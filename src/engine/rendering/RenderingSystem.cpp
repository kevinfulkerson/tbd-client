#include "RenderingSystem.hpp"
#include <iostream>
#include <string>

RenderingSystem::RenderingSystem() : m_pWindow(nullptr),
                                     m_pScreenSurface(nullptr),
                                     m_pImage(nullptr)
{
    m_previousFrameTime_ms = m_frameTime_ms = SDL_GetTicks();
}

/* virtual */
RenderingSystem::~RenderingSystem()
{
}

void RenderingSystem::Init()
{
    // Initialize the SDL subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init: " << SDL_GetError() << std::endl;
    }

    // Create an SDL window
    m_pWindow = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (m_pWindow == nullptr)
    {
        std::cout << "SDL_CreateWindow: " << SDL_GetError() << std::endl;
    }

    // Get the window surface for the window we just opened
    m_pScreenSurface = SDL_GetWindowSurface(m_pWindow);
    if (m_pScreenSurface == nullptr)
    {
        std::cout << "SDL_GetWindowSurface: " << SDL_GetError() << std::endl;
    }

    // Open a bmp file
    // Admittedly, this is very dependent on location of executable
    m_pImage = SDL_LoadBMP("../res/skelly-test.bmp");
    if (m_pImage == nullptr)
    {
        std::cout << "SDL_LoadBMP: " << SDL_GetError() << std::endl;
    }
}

void RenderingSystem::SetFPS(uint32_t fps)
{
    m_frameTime_ms = 1000.f/fps;
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
    // Draw our surface image
    SDL_BlitSurface(m_pImage, nullptr, m_pScreenSurface, nullptr);
    SDL_UpdateWindowSurface(m_pWindow);
}