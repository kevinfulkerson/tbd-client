#ifndef _INPUTSYSTEM_H_
#define _INPUTSYSTEM_H_

#include <functional>

#include "SDL2/SDL.h"

namespace tbd
{
    class InputSystem
    {
      public:
        InputSystem();
        virtual ~InputSystem();

        bool Init();
        int RegisterEventHandler(SDL_Keycode key, std::function<void()> handler);
        int HandleInput();

      private:
        void doNothing();

        SDL_Event m_event;

        // TODO: create a vector of key events to commands
        bool m_isQPressed;
        std::function<void()> m_qPressHandler;
    };
}

#endif //_INPUTSYSTEM_H_