#ifndef LOADING_HELPERS_H
#define LOADING_HELPERS_H
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>

#include <string>

SDL_Texture* load_texture(std::string const& path, SDL_Renderer* renderer);

#endif
