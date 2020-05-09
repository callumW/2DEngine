#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL.h>

typedef struct texture_t {
    SDL_Texture* tex = nullptr;
    int width = -1;
    int height = -1;
} texture_t;
#endif
