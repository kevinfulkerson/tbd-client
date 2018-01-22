#include <iostream>
#include "SDL.h"

int main(int, char *[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init: " << SDL_GetError() << std::endl;
        return -1;
    }

    auto *pWindow = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (pWindow == nullptr) {
        std::cout << "SDL_CreateWindow: " << SDL_GetError() << std::endl;
        return -1;
    }

    auto *pScreenSurface = SDL_GetWindowSurface(pWindow);
    if (pScreenSurface == nullptr) {
        std::cout << "SDL_GetWindowSurface: " << SDL_GetError() << std::endl;
        return -1;
    }

    auto *pImage = SDL_LoadBMP("./resources/skelly-test.bmp");
    if (pImage == nullptr) {
        std::cout << "SDL_LoadBMP: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_BlitSurface(pImage, nullptr, pScreenSurface, nullptr);
    SDL_UpdateWindowSurface(pWindow);

    SDL_Delay(2000);

    SDL_FreeSurface(pScreenSurface);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    return 0;
}