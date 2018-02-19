#include "src/engine/core/Engine.hpp"

#include <cstdio>
#include <iostream>

namespace tbd
{
    Engine::Engine() : m_sdlInitialized(false),
                       m_running(true),
                       m_pRenderingSystem(nullptr),
                       m_pInputSystem(nullptr)
    {
    }

    /* virtual */
    Engine::~Engine()
    {
        if (m_pRenderingSystem)
        {
            m_pRenderingSystem->Close();
            delete m_pRenderingSystem;
        }

        if (m_pInputSystem)
        {
            delete m_pInputSystem;
        }

        if (m_sdlInitialized)
        {
            SDL_Quit();
        }
    }

    bool Engine::Init()
    {
        // Initialize the SDL subsystem
        // Uses explicit inclusion (ignoring implied includes)
        if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
        {
            // We can go no further, just report and quit
            std::cout << "SDL_Init: " << SDL_GetError() << std::endl;
            return false;
        }

        m_sdlInitialized = true;
        m_pRenderingSystem = new RenderingSystem();
        m_pInputSystem = new InputSystem();

        // Attempt to initialize each system
        // Should eventually change this to iterate through a list or something
        // else smart
        if (!m_pRenderingSystem->Init())
        {
            return false;
        }

        if (!m_pInputSystem->Init())
        {
            return false;
        }

        // Perform any additional initializations
        m_pRenderingSystem->SetFPS(60);
        m_pInputSystem->RegisterEventHandler(
            SDLK_w,
            std::bind(&RenderingSystem::MoveCameraUp, this->m_pRenderingSystem));
        m_pInputSystem->RegisterEventHandler(
            SDLK_s,
            std::bind(&RenderingSystem::MoveCameraDown, this->m_pRenderingSystem));

        return true;
    }

    void Engine::Start()
    {
        while (m_running)
        {
            // Poll for any events on the queue
            if (m_pInputSystem->HandleInput() == -1)
            {
                this->Stop();
            }

            if (m_pRenderingSystem->ApplyRenderingStrategy())
            {
                m_pRenderingSystem->Render();
            }
            else
            {
                SDL_Delay(1);
            }
        }
    }

    void Engine::Stop()
    {
        m_running = false;
    }
}