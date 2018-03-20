#ifndef _IINPUTHANDLER_H_
#define _IINPUTHANDLER_H_

#include "SDL2/SDL.h"

#include "src/engine/input/InputSystem.hpp"

namespace tbd
{
    class IInputHandler
    {
      public:
        virtual ~IInputHandler() {}
        virtual void Init(const CommandMap &commandMap) = 0;
        virtual void HandleEvent(const SDL_Event &event) = 0;
    };
}

#endif //_IINPUTHANDLER_H_