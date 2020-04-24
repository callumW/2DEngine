#include <SDL.h>
#include <iostream>


int main(int argc, char* argv[])
{
    std::cout << "Welcome to " << argv[0] << std::endl;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "failed to init SDL" << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("terminal-reboot", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, 600, 400, SDL_WINDOW_VULKAN);

    if (window == nullptr) {
        std::cout << "failed to create window: " << SDL_GetError() << std::endl;
    }
    else {
        SDL_Event e;
        bool quit = false;
        while (!quit) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                if (e.type == SDL_KEYDOWN) {
                    quit = true;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    quit = true;
                }
            }
        }
        SDL_DestroyWindow(window);
    }


    SDL_Quit();

    return 0;
}
