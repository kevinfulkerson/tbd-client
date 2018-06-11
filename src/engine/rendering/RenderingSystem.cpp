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

        const GLint elementIndexData[] = {
            0, 1, 2
        };

        glGenBuffers(1, &m_vertexBuffer);
        glGenBuffers(1, &m_elementBuffer);
        
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData),
            vertexBufferData, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementIndexData),
            elementIndexData, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        Shader shaderTest;
        shaderTest.AddShader("../res/vertex_test.shader", GL_VERTEX_SHADER);
        shaderTest.AddShader("../res/fragment_test.shader", GL_FRAGMENT_SHADER);
        shaderTest.LinkProgram();

        m_shaders.push_back(shaderTest);

        // Generate the model-view-projection matrix components
        m_currentCamera.SetAspectRatio(640.f / 480.f);
        m_currentCamera.SetFOVDegrees(45.f);
        m_currentCamera.SetNear(0.1f);
        m_currentCamera.SetFar(100.f);

        m_currentCamera.SetLocation(glm::vec3(0.f, 1.5f, 3.f));
        m_currentCamera.SetFacing(glm::vec3(0.f, 0.f, 0.f));
        m_currentCamera.SetUp(glm::vec3(0.f, 1.f, 0.f));

        glm::mat4 model = glm::mat4(1.f);

        // Combine the components
        m_mvp = m_currentCamera.GetProjectionMatrix() *
                m_currentCamera.GetViewMatrix() *
                model;

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

        glBindVertexArray(m_vertexBuffer);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

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

    void RenderingSystem::MoveCameraUp()
    {
        m_currentCamera.MoveLocation(glm::vec3(0.f, 0.1f, 0.f));
        glm::mat4 model = glm::mat4(1.f);

        // Combine the components
        m_mvp = m_currentCamera.GetProjectionMatrix() *
                m_currentCamera.GetViewMatrix() *
                model;
        m_testVal = true;
    }

    void RenderingSystem::MoveCameraDown()
    {
        m_currentCamera.MoveLocation(glm::vec3(0.f, -0.1f, 0.f));
        glm::mat4 model = glm::mat4(1.f);

        // Combine the components
        m_mvp = m_currentCamera.GetProjectionMatrix() *
                m_currentCamera.GetViewMatrix() *
                model;
    }
}