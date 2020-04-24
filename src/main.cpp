#include <SDL.h>
#include <iostream>


int main(int argc, char* argv[])
{
    std::cout << "Welcome to " << argv[0] << std::endl;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "failed to init SDL" << std::endl;
        return 1;
    }

    SDL_Window* window =
        SDL_CreateWindow("terminal-reboot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600,
                         400, SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cout << "failed to create window: " << SDL_GetError() << std::endl;
    }
    else {

        SDL_Surface* surface = SDL_GetWindowSurface(window);

        SDL_FillRect(surface, nullptr, 0xffffff);

        if (surface) {
            SDL_Surface* img_surface = SDL_LoadBMP("./G.bmp");
            if (img_surface == nullptr) {
                std::cout << "Failed to load bitmap: " << SDL_GetError() << std::endl;
            }
            else {
                if (0 != SDL_BlitSurface(img_surface, nullptr, surface, nullptr)) {
                    std::cout << "Failed to blit surface" << std::endl;
                }
                else {
                    SDL_UpdateWindowSurface(window);
                }
            }
        }
        else {
            std::cout << "Failed to load window surface: " << SDL_GetError() << std::endl;
        }

        SDL_Event e;
        bool quit = false;
        while (!quit) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }
        }
        SDL_DestroyWindow(window);
    }


    SDL_Quit();

    return 0;
}
