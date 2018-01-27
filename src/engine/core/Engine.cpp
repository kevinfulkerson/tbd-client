#include "Engine.hpp"
#include <cstdio>
#include <iostream>

Engine::Engine() : m_running(true)
{
}

/* virtual */
Engine::~Engine()
{
}

void Engine::Init()
{
    m_pRenderingSystem = new RenderingSystem();
    m_pInputSystem = new InputSystem();

    m_pRenderingSystem->Init();
    m_pRenderingSystem->SetFPS(60);

    m_pInputSystem->Init();
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