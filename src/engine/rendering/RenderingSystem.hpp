#ifndef _RENDERINGSYSTEM_H_
#define _RENDERINGSYSTEM_H_

#include <cstdint>
#include <vector>

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "glm/glm.hpp"

#include "src/engine/rendering/Shader.hpp"
#include "src/engine/rendering/Camera.hpp"

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

        void MoveCameraUp();
        void MoveCameraDown();

      private:
        SDL_Window *m_pWindow;
        SDL_GLContext m_pGLContext;
        Camera m_currentCamera;

        GLuint m_vertexBuffer;
        GLuint m_elementBuffer;
        std::vector<Shader> m_shaders;
        glm::mat4 m_mvp;

        uint32_t m_previousFrameTime_ms;
        uint32_t m_frameTime_ms;

        bool m_testVal;
    };
}

#endif //_RENDERINGSYSTEM_H_