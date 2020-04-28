#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H
#include <SDL2/SDL.h>

#include "entity_id.h"


typedef struct render_component_t {
    entity_id_t entity_id;
    bool hidden;
    SDL_Texture* texture;
    SDL_Rect src_rect;
    SDL_Rect dst_rect;
    double rotation;
    SDL_Point pivot_point;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
} render_component_t;
#endif
