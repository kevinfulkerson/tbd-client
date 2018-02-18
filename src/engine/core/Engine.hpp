#include "SDL2/SDL.h"

#include "src/engine/rendering/RenderingSystem.hpp"
#include "src/engine/input/InputSystem.hpp"

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