#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H
#include <SDL2/SDL.h>
#include <box2d/box2d.h>

#include "Animation.h"
#include "ComponentManager.h"
#include "Entity.h"
#include "Texture.h"

typedef struct render_component_t {
    bool hidden = false;
    bool is_animated = false;
    texture_t texture;
    SDL_Rect dst_rect;
    double rotation;
    SDL_Point pivot_point;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    animation_t animation;

    b2Body* physics_body = nullptr;

    void reset()
    {
        hidden = false;
        texture = {};
        dst_rect = {};
        rotation = 0.0;
        pivot_point = {};
        flip = SDL_FLIP_NONE;
    }

    void set_position(vec2f_t const& pos)
    {
        dst_rect.x = static_cast<int>(pos.x) - texture.src_rect.w / 2;
        dst_rect.y = static_cast<int>(pos.y) - texture.src_rect.h / 2;
    }

    void set_position(b2Vec2 const& pos)
    {
        dst_rect.x = static_cast<int>(pos.x) - texture.src_rect.w / 2;
        dst_rect.y = static_cast<int>(pos.y) - texture.src_rect.h / 2;
    }
} render_component_t;
#endif
