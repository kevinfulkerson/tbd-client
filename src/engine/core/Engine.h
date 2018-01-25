#include "SDL.h"

class Engine
{
  public:
    Engine();
    virtual ~Engine();

    void Start();
    void Stop();

  private:
    SDL_Window *m_pWindow;
    SDL_Surface *m_pScreenSurface;
    SDL_Surface *m_pImage;
    bool m_running;
};