#include "loading_helpers.h"

SDL_Texture* load_texture(std::string const& path, SDL_Renderer* renderer)
{
    SDL_Texture* ret = nullptr;
    SDL_Surface* tmp = SDL_LoadBMP(path.c_str());

    if (tmp) {
        ret = SDL_CreateTextureFromSurface(renderer, tmp);
        SDL_FreeSurface(tmp);
    }
    return ret;
}
