#include "SDL2/SDL.h"

class InputSystem
{
  public:
    InputSystem();
    virtual ~InputSystem();

    bool Init();
    int HandleInput();

  private:
    SDL_Event m_event;
};