#include "Entity.h"
#include "Globals.h"
#include "loading_helpers.h"

#include <cmath>
#include <iostream>

Entity::Entity()
{
    tex = load_default_texture();

    tex_src.w = 40;
    tex_src.h = 40;

    draw_dest.w = 40;
    draw_dest.h = 40;

    rot_pivot.x = tex_src.w / 2;
    rot_pivot.y = tex_src.h / 2;
}

Entity::Entity(std::string const& texture_path, SDL_Rect const& src)
{
    tex = load_texture(texture_path);
    tex_src = src;

    draw_dest.w = tex_src.w;
    draw_dest.h = tex_src.h;

    rot_pivot.x = tex_src.w / 2;
    rot_pivot.y = tex_src.h / 2;
}

void Entity::render()
{
    if (!hidden) {
        if (tex) {
            SDL_RenderCopyEx(g_renderer, tex, &tex_src, &draw_dest, rot, &rot_pivot, SDL_FLIP_NONE);
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

void Entity::set_rotation(double new_rot) { rot = new_rot; }

void Entity::add_child(Entity* node)
{
    if (node) {
        children.push_back(node);
        node->parent = this;
    }
}

void Entity::update_render_position()
{
    draw_dest.x = static_cast<Sint32>(world_pos.x) - (tex_src.w / 2);
    draw_dest.y = static_cast<Sint32>(world_pos.y) - (tex_src.h / 2);
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
