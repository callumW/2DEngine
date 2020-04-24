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
            SDL_RenderCopyEx(g_renderer, tex, &tex_src, &draw_dest, world_rot, &rot_pivot,
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

void Entity::set_world_pos(vec2f_t new_pos)
{
    world_pos = new_pos;
    if (parent != nullptr) {
        local_pos = world_pos - parent->world_pos;
    }
    else {
        local_pos = world_pos;
    }
    update_render_position();
    update_children_positions();
}

void Entity::set_local_pos(vec2f_t new_pos)
{
    local_pos = new_pos;
    if (parent != nullptr) {
        world_pos = parent->world_pos + local_pos;
    }
    else {
        world_pos = local_pos;
    }
    update_render_position();
    update_children_positions();
}

void Entity::set_world_rot(double new_rot)
{
    world_rot = new_rot;

    if (parent != nullptr) {
        local_rot = world_rot - parent->world_rot;
    }
    else {
        local_rot = world_rot;
    }
}

void Entity::set_local_rot(double new_rot)
{
    local_rot = new_rot;
    if (parent != nullptr) {
        world_rot = parent->world_rot + local_rot;
    }
    else {
        world_rot = local_rot;
    }
}

void Entity::add_child(Entity* node)
{
    if (node) {
        children.push_back(node);
        node->parent = this;
    }
}

void Entity::update_render_position()
{
    draw_dest.x = static_cast<Sint32>(world_pos.x);
    draw_dest.y = static_cast<Sint32>(world_pos.y);
}

void Entity::apply_forces(float const delta_time)
{
    vec2f_t new_pos = world_pos + (force * delta_time);
    set_world_pos(new_pos);
}

void Entity::update_children_positions()
{
    for (auto& child : children) {
        child->update_relative_position();
    }
}

void Entity::update_relative_position()
{
    world_pos = parent->world_pos + local_pos;
    update_render_position();
}

void Entity::remove_child(Entity* node)
{
    if (node == nullptr) {
        return;
    }

    auto end = children.end();
    for (auto it = children.begin(); it != end; it++) {
        if (*it == node) {
            children.erase(it);
            (*it)->parent = nullptr;
            return;
        }
    }
}
