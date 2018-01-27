#include "SDL.h"

class RenderingSystem
{
  public:
    RenderingSystem();
    virtual ~RenderingSystem();

    void Init();
    void Render();

  private:
    SDL_Window *m_pWindow;
    SDL_Surface *m_pScreenSurface;
    SDL_Surface *m_pImage;
};