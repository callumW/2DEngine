#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <iostream>

#include "Game.h"
#include "Globals.h"
#include "input.h"


SDL_Renderer* g_renderer;
SDL_Window* g_window;

int const WINDOW_WIDTH = 600;
int const WINDOW_HEIGHT = 400;

Uint32 const TARGET_FRAME_DELTA = 8;

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
        wave_file = Mix_LoadWAV("./assets/more_good_wind.wav");
        if (wave_file == nullptr) {
            std::cout << "Failed to load wav file" << std::endl;
        }
        else {
            Mix_PlayChannel(-1, wave_file, -1);
        }
    }

    g_window = SDL_CreateWindow("terminal-reboot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN);

    if (g_window == nullptr) {
        std::cout << "failed to create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

    if (g_renderer == nullptr) {
        std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    Game game;

    SDL_Event e;
    bool quit = false;
    int frame_count = 0;
    Uint32 last_frame_count_time = SDL_GetTicks();
    Uint32 now = 0;
    Uint32 last = last_frame_count_time;
    Uint32 frame_time_accumulator = 0;
    Uint32 delta = 0;
    Uint32 render_time = 0;
    Uint32 sleep_time = 0;
    while (!quit) {
        now = SDL_GetTicks();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
                continue;
            }
            update_input_struct(e);
        }

        delta = now - last;
        last = now;

        if ((now - last_frame_count_time) >= 1000) {
            std::cout << "FPS: " << frame_count << " | " << (frame_time_accumulator / frame_count)
                      << "ms" << std::endl;
            frame_count = 0;
            frame_time_accumulator = 0;
            last_frame_count_time = now;
        }

        game.update(delta);

        // render
        SDL_RenderClear(g_renderer);
        game.render();
        SDL_RenderPresent(g_renderer);

        frame_count++;
        // Sleep to maintain constant FPS
        render_time = SDL_GetTicks() - now;
        frame_time_accumulator += render_time;
        if (render_time < TARGET_FRAME_DELTA) {
            sleep_time = TARGET_FRAME_DELTA - render_time;
            SDL_Delay(sleep_time);
        }
    }

    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);

    if (wave_file)
        Mix_FreeChunk(wave_file);

    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
