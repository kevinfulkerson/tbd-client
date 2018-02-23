#include "src/engine/core/Engine.hpp"
#include "src/engine/input/commands/CommandFunc.hpp"

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

        CommandScheme scheme;
        scheme.holdAcceleration = 0;
        scheme.holdDelay = 0;
        scheme.holdPeriod = 0;
        scheme.longPressDuration = 500;
        scheme.pressDuration = 0;
        m_pInputSystem = new InputSystem(scheme);

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

        CommandType wType;
        wType.key = SDLK_w;
        wType.style = CommandStyle::Hold;
        m_pInputSystem->RegisterEventHandler(
            wType, CommandAttachPoint::Unset,
            std::make_unique<CommandFunc>(std::bind(
                &RenderingSystem::MoveCameraUp, this->m_pRenderingSystem)));

        CommandType sType;
        sType.key = SDLK_s;
        sType.style = CommandStyle::LongPress;
        m_pInputSystem->RegisterEventHandler(
            sType, CommandAttachPoint::Start,
            std::make_unique<CommandFunc>(std::bind(
                &RenderingSystem::MoveCameraDown, this->m_pRenderingSystem)));

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