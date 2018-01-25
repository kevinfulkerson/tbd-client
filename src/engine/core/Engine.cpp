#include "Engine.h"
#include <iostream>

Engine::Engine() : m_pWindow(nullptr),
                   m_pScreenSurface(nullptr),
                   m_pImage(nullptr),
                   m_running(false)
{
}

/* virtual */
Engine::~Engine()
{
    // Free all the stuff we loaded before
    SDL_FreeSurface(m_pScreenSurface);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}

void Engine::Start()
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

    m_running = true;
    SDL_Event event;

    while (m_running)
    {
        // Poll for any events on the queue
        while (SDL_PollEvent(&event) == 1)
        {
            // Check if this event directs us to quit the application
            if (event.type == SDL_QUIT)
            {
                this->Stop();
            }
        }

        // Draw our surface image
        SDL_BlitSurface(m_pImage, nullptr, m_pScreenSurface, nullptr);
        SDL_UpdateWindowSurface(m_pWindow);
    }
}

void Engine::Stop()
{
    m_running = false;
}