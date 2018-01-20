#include <iostream>
#include "SDL.h"

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init" << std::endl;
        return -1;
    }

    auto *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        std::cout << "SDL_CreateWindow" << std::endl;
        return -1;
    }

    SDL_DestroyWindow(win);
    SDL_Quit();
}