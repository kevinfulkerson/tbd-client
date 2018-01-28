#include "SDL2/SDL.h"
#include <cstdint>

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

private:
  SDL_Window *m_pWindow;
  SDL_GLContext m_pGLContext;

  uint32_t m_previousFrameTime_ms;
  uint32_t m_frameTime_ms;
};