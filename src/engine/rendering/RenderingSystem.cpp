#include "src/engine/rendering/RenderingSystem.hpp"

#include <iostream>
#include <string>

#include "glm/ext.hpp"

namespace tbd
{
    RenderingSystem::RenderingSystem() : m_pWindow(nullptr),
                                         m_pGLContext(nullptr),
                                         m_vertexBuffer(0),
                                         m_testVal(true)
    {
        m_previousFrameTime_ms = SDL_GetTicks();
        m_frameTime_ms = 1000 / 60;
    }

    /* virtual */
    RenderingSystem::~RenderingSystem()
    {
    }

    bool RenderingSystem::Init()
    {
        bool initialized = true;

        // Create an SDL window
        m_pWindow = SDL_CreateWindow("TBD Client",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     640, 480,
                                     SDL_WINDOW_OPENGL);
        if (m_pWindow == nullptr)
        {
            std::cout << "SDL_CreateWindow: " << SDL_GetError() << std::endl;
            return false;
        }

        m_pGLContext = SDL_GL_CreateContext(m_pWindow);
        if (m_pGLContext == nullptr)
        {
            std::cout << "SDL_GL_CreateContext: " << SDL_GetError() << std::endl;
            return false;
        }

        if (glewInit() != GLEW_OK)
        {
            std::cout << "glewInit: Failed to initialize GLEW" << std::endl;
            return false;
        }

        GLuint vertexArrayId;
        glGenVertexArrays(1, &vertexArrayId);
        glBindVertexArray(vertexArrayId);

        const GLfloat vertexBufferData[] = {
            -1.f, 0.f, 1.f,
            1.f, 0.f, 1.f,
            0.f, 0.f, -1.f};

        glGenBuffers(1, &m_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData),
                     vertexBufferData, GL_STATIC_DRAW);

        Shader shaderTest;
        shaderTest.AddShader("../res/vertex_test.shader", GL_VERTEX_SHADER);
        shaderTest.AddShader("../res/fragment_test.shader", GL_FRAGMENT_SHADER);
        shaderTest.LinkProgram();

        m_shaders.push_back(shaderTest);

        // Generate the model-view-projection matrix components
        glm::mat4 projection = glm::perspective(
            glm::radians(45.f), 640.f / 480.f, 0.1f, 100.f);
        glm::mat4 view = glm::lookAt(
            glm::vec3(0.f, 1.f, 3.f),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f, 1.f, 0.f));
        glm::mat4 model = glm::mat4(1.f);

        // Combine the components
        m_mvp = projection * view * model;

        return initialized;
    }

    void RenderingSystem::SetFPS(uint32_t fps)
    {
        m_frameTime_ms = 1000 / fps;
    }

    bool RenderingSystem::ApplyRenderingStrategy()
    {
        bool renderFrame = false;

        uint32_t currentFrameTime = SDL_GetTicks();
        if (currentFrameTime - m_previousFrameTime_ms > m_frameTime_ms)
        {
            m_previousFrameTime_ms = currentFrameTime;
            renderFrame = true;
        }

        return renderFrame;
    }

    void RenderingSystem::Render()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto it = m_shaders.begin();
        auto end = m_shaders.end();
        for (; it != end; ++it)
        {
            // Cache the id for this shader program
            GLuint programId = (*it).GetProgramId();

            // Apply the matrix to the shader
            GLuint matrixId = glGetUniformLocation(programId, "mvp");
            glUniformMatrix4fv(matrixId, 1, GL_FALSE, &m_mvp[0][0]);

            glUseProgram(programId);
        }

        // Vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
        glVertexAttribPointer(
            0,        // index of vertex attribute to modify
            3,        // size
            GL_FLOAT, // type
            GL_FALSE, // normalized
            0,        // stride
            (void *)0 // vertex attribute array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        SDL_GL_SwapWindow(m_pWindow);
    }

    void RenderingSystem::Close()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &m_vertexBuffer);

        if (m_pGLContext)
        {
            SDL_GL_DeleteContext(m_pGLContext);
        }

        if (m_pWindow)
        {
            SDL_DestroyWindow(m_pWindow);
        }

        auto it = m_shaders.begin();
        auto end = m_shaders.end();
        for (; it != end; ++it)
        {
            (*it).DeleteProgram();
        }
    }

    void RenderingSystem::DeleteMe()
    {
        if (m_testVal)
        {
            glm::mat4 projection = glm::perspective(
                glm::radians(45.f), 640.f / 480.f, 0.1f, 100.f);
            glm::mat4 view = glm::lookAt(
                glm::vec3(0.f, 1.5f, 3.f),
                glm::vec3(0.f, 0.f, 0.f),
                glm::vec3(0.f, 1.f, 0.f));
            glm::mat4 model = glm::mat4(1.f);

            // Combine the components
            m_mvp = projection * view * model;
            m_testVal = false;
        }
        else
        {
            glm::mat4 projection = glm::perspective(
                glm::radians(45.f), 640.f / 480.f, 0.1f, 100.f);
            glm::mat4 view = glm::lookAt(
                glm::vec3(0.f, 1.f, 3.f),
                glm::vec3(0.f, 0.f, 0.f),
                glm::vec3(0.f, 1.f, 0.f));
            glm::mat4 model = glm::mat4(1.f);

            // Combine the components
            m_mvp = projection * view * model;
            m_testVal = true;
        }
    }
}