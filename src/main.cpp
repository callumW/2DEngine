#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <iostream>

#include "input.h"

int main(int argc, char* argv[])
{
    std::cout << "Welcome to " << argv[0] << std::endl;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "failed to init SDL" << std::endl;
        return 1;
    }
    Mix_Chunk* wave_file = nullptr;
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) != 0) {
        std::cout << "Failed to open audio system" << std::endl;
    }
    else {
        wave_file = Mix_LoadWAV("./more_good_wind.wav");
        if (wave_file == nullptr) {
            std::cout << "Failed to load wav file" << std::endl;
        }
        else {
            Mix_PlayChannel(-1, wave_file, -1);
        }
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

                update_input_struct(e);
            }
        }
        SDL_DestroyWindow(window);
    }

    if (wave_file)
        Mix_FreeChunk(wave_file);

    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
