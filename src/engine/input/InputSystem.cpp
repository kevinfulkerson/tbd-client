#include "InputSystem.hpp"

InputSystem::InputSystem()
{
}

/* virtual */
InputSystem::~InputSystem()
{
}

void InputSystem::Init()
{
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
    }

    return retVal;
}