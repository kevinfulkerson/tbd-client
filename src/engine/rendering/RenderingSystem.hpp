#include "SDL.h"
#include <cstdint>

class RenderingSystem
{
public:
  RenderingSystem();
  virtual ~RenderingSystem();

  void Init();
  void SetFPS(uint32_t fps);
  bool ApplyRenderingStrategy();
  void Render();

private:
  SDL_Window *m_pWindow;
  SDL_Surface *m_pScreenSurface;
  SDL_Surface *m_pImage;

  uint32_t m_previousFrameTime_ms;
  uint32_t m_frameTime_ms;
};