#include <iostream>
#include "SDL.h"

int main(int, char *[]) {
    // Initialize the SDL subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create an SDL window
    auto *pWindow = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (pWindow == nullptr) {
        std::cout << "SDL_CreateWindow: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Get the window surface for the window we just opened
    auto *pScreenSurface = SDL_GetWindowSurface(pWindow);
    if (pScreenSurface == nullptr) {
        std::cout << "SDL_GetWindowSurface: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Open a bmp file
    // Admittedly, this is very dependent on location of executable
    auto *pImage = SDL_LoadBMP("../res/skelly-test.bmp");
    if (pImage == nullptr) {
        std::cout << "SDL_LoadBMP: " << SDL_GetError() << std::endl;
        return -1;
    }

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        // Poll for any events on the queue
        while (SDL_PollEvent(&event) == 1) {
            // Check if this event directs us to quit the application
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Draw our surface image
        SDL_BlitSurface(pImage, nullptr, pScreenSurface, nullptr);
        SDL_UpdateWindowSurface(pWindow);
    }

    // Free all the stuff we loaded before
    SDL_FreeSurface(pScreenSurface);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    return 0;
}