#include <iostream>
#include "SDL.h"
#include <include/logging/Logger.h>

using namespace TBD;

int main(int argc, char* argv[])
{
    Logger logger(Priority::Error);
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        logger.log(std::cout, Priority::Error, "SDL_Init");
        return -1;
    }

    auto *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        logger.log(std::cout, Priority::Error, "SDL_CreateWindow");
        return -1;
    }

    SDL_DestroyWindow(win);
    SDL_Quit();
}