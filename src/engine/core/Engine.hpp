#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "SDL2/SDL.h"

#include "src/engine/input/InputSystem.hpp"
#include "src/engine/rendering/RenderingSystem.hpp"

namespace tbd
{
    class Engine
    {
      public:
        Engine();
        virtual ~Engine();

        bool Init();
        void Start();
        void Stop();

      private:
        bool m_sdlInitialized;
        bool m_running;
        RenderingSystem *m_pRenderingSystem;
        InputSystem *m_pInputSystem;
    };
}

#endif //_ENGINE_H_