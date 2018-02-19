#include "src/engine/input/InputSystem.hpp"

namespace tbd
{
    InputSystem::InputSystem() : m_isWPressed(false),
                                 m_isSPressed(false)
    {
        this->m_wPressHandler = std::bind(&InputSystem::doNothing, this);
        this->m_sPressHandler = std::bind(&InputSystem::doNothing, this);
    }

    /* virtual */
    InputSystem::~InputSystem()
    {
    }

    bool InputSystem::Init()
    {
        return true;
    }

    int InputSystem::RegisterEventHandler(SDL_Keycode key,
                                          std::function<void()> handler)
    {
        if (key == SDLK_w)
        {
            this->m_wPressHandler = handler;
        }
        else if (key == SDLK_s)
        {
            this->m_sPressHandler = handler;
        }

        return 0;
    }

    int InputSystem::HandleInput()
    {
        int retVal = 0;

        while (SDL_PollEvent(&m_event) == 1)
        {
            // Check if this event directs us to quit the application
            if (m_event.type == SDL_QUIT)
            {
                retVal = -1;
            }
            else if (m_event.type == SDL_KEYDOWN)
            {
                if (m_event.key.keysym.sym == SDLK_w)
                {
                    this->m_isWPressed = true;
                }
                else if (m_event.key.keysym.sym == SDLK_s)
                {
                    this->m_isSPressed = true;
                }
            }
            else if (m_event.type == SDL_KEYUP)
            {
                if (m_event.key.keysym.sym == SDLK_w)
                {
                    if (this->m_isWPressed)
                    {
                        this->m_wPressHandler();
                        this->m_isWPressed = false;
                    }
                }
                else if (m_event.key.keysym.sym == SDLK_s)
                {
                    if (this->m_isSPressed)
                    {
                        this->m_sPressHandler();
                        this->m_isSPressed = false;
                    }
                }
            }
        }

        return retVal;
    }
}