#include "Engine.h"
#include <iostream>

Engine::Engine() : m_running(false)
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
    m_pInputSystem->Init();
}

void Engine::Start()
{
    m_running = true;

    while (m_running)
    {
        // Poll for any events on the queue
        if (m_pInputSystem->HandleInput() == -1)
        {
            this->Stop();
        }

        m_pRenderingSystem->Render();
    }
}

void Engine::Stop()
{
    m_running = false;
}