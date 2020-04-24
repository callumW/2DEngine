#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>

#include <vector>

#include "game_math.h"

class Entity {
public:
    Entity();

    virtual void render();
    virtual void update(float delta);

    virtual void set_world_pos(vec2f_t new_pos);

    virtual void set_local_pos(vec2f_t new_pos);

    virtual void set_rotation(double new_rot);

    virtual void set_hidden(bool hide = true) { hidden = hide; }

    virtual void set_force(vec2f_t new_force) { force = new_force; }
    virtual void add_force(vec2f_t add) { force += add; }

    virtual void add_child(Entity* node);

    virtual void remove_child(Entity* node);

    bool is_hidden() const { return hidden; }

    vec2f_t world_position() const { return world_pos; }
    vec2f_t local_position() const { return local_pos; }

    double rotation() const { return rot; }

protected:
    void update_render_position();
    void apply_forces(float const delta_time);

    void update_children_positions();
    void update_relative_position();

    std::vector<Entity*> children;
    Entity* parent = nullptr;

    vec2f_t world_pos;
    vec2f_t local_pos;
    double rot = 0.0f; // rotation in degrees

    bool hidden = false;

    SDL_Texture* tex = nullptr;
    SDL_Rect tex_src = {0};
    SDL_Rect draw_dest = {0};
    SDL_Point rot_pivot = {0};

    vec2f_t force = {0.0f, 0.0f};
};
#endif
