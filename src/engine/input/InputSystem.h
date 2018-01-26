#include "SDL.h"

class InputSystem
{
    public:
        InputSystem();
        virtual ~InputSystem();

        void Init();
        int HandleInput();

    private:
        SDL_Event m_event;
};