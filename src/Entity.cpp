#include "Entity.h"
#include "Globals.h"

#include <iostream>

Entity::Entity()
{
    tex = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 40, 40);

    tex_src.w = 40;
    tex_src.h = 40;

    draw_dest.w = 40;
    draw_dest.h = 40;

    if (tex == nullptr) {
        std::cout << "Failed to create default texture" << std::endl;
    }
    else {
        SDL_SetRenderTarget(g_renderer, tex);
        SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);
        SDL_RenderClear(g_renderer);
        SDL_RenderDrawRect(g_renderer, &tex_src);
        SDL_SetRenderTarget(g_renderer, nullptr);
        SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
    }
}

void Entity::render()
{
    if (!hidden) {
        if (tex) {
            SDL_RenderCopyEx(g_renderer, tex, &tex_src, &draw_dest, rotation, &rot_pivot,
                             SDL_FLIP_NONE);
        }

        for (auto& child : children) {
            child->render();
        }
    }
}

void Entity::update(float delta)
{
    apply_forces(delta);
    for (auto& child : children) {
        child->update(delta);
    }
}

void Entity::update_render_position()
{
    draw_dest.x = static_cast<Sint32>(position.x);
    draw_dest.y = static_cast<Sint32>(position.y);
}

void Entity::apply_forces(float const delta_time)
{
    position += (force * delta_time);
    update_render_position();
}
