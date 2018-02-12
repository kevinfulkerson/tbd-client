#include "InputSystem.hpp"

InputSystem::InputSystem() : m_isQPressed(false)
{
    this->m_qPressHandler = std::bind(&InputSystem::doNothing, this);
}

/* virtual */
InputSystem::~InputSystem()
{
}

bool InputSystem::Init()
{
    return true;
}

int InputSystem::RegisterEventHandler(SDL_Keycode key, std::function<void()> handler)
{
    if (key == SDLK_q)
    {
        this->m_qPressHandler = handler;
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
            if (m_event.key.keysym.sym == SDLK_q)
            {
                this->m_isQPressed = true;
            }
        }
        else if (m_event.type == SDL_KEYUP)
        {
            if (m_event.key.keysym.sym == SDLK_q)
            {
                if (this->m_isQPressed)
                {
                    this->m_qPressHandler();
                    this->m_isQPressed = false;
                }
            }
        }
    }

    return retVal;
}

void InputSystem::doNothing()
{
}