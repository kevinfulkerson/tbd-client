#include "RenderingSystem.hpp"
#include <iostream>
#include <string>

RenderingSystem::RenderingSystem() : m_pWindow(nullptr),
                                     m_pGLContext(nullptr),
                                     m_vertexBuffer(0)
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
                                 0, 0,
                                 SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
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

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    const GLfloat vertexBufferData[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

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
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
}