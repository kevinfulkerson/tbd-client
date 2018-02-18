#ifndef _RENDERINGSYSTEM_H_
#define _RENDERINGSYSTEM_H_

#include <cstdint>
#include <vector>

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "glm/glm.hpp"

#include "src/engine/rendering/Shader.hpp"

namespace tbd
{
    class RenderingSystem
    {
      public:
        RenderingSystem();
        virtual ~RenderingSystem();

        bool Init();
        void SetFPS(uint32_t fps);
        bool ApplyRenderingStrategy();
        void Render();
        void Close();

        void DeleteMe();

      private:
        SDL_Window *m_pWindow;
        SDL_GLContext m_pGLContext;

        GLuint m_vertexBuffer;
        std::vector<Shader> m_shaders;
        glm::mat4 m_mvp;

        uint32_t m_previousFrameTime_ms;
        uint32_t m_frameTime_ms;

        bool m_testVal;
    };
}

#endif //_RENDERINGSYSTEM_H_