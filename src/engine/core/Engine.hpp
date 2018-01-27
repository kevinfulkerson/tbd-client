#include "SDL.h"
#include "../rendering/RenderingSystem.hpp"
#include "../input/InputSystem.hpp"

class Engine
{
public:
  Engine();
  virtual ~Engine();

  void Init();
  void Start();
  void Stop();

private:
  bool m_running;
  RenderingSystem *m_pRenderingSystem;
  InputSystem *m_pInputSystem;
};