#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H
#include <SDL2/SDL.h>

#include "ComponentManager.h"
#include "Entity.h"


typedef struct render_component_t {
    bool hidden = false;
    SDL_Texture* texture = nullptr;
    SDL_Rect src_rect;
    SDL_Rect dst_rect;
    double rotation;
    SDL_Point pivot_point;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    void reset()
    {
        hidden = false;
        texture = nullptr;
        src_rect = {};
        dst_rect = {};
        rotation = 0.0;
        pivot_point = {};
        flip = SDL_FLIP_NONE;
    }
} render_component_t;
#endif
