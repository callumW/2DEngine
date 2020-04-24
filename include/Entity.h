#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>

#include <vector>

#include "game_math.h"

class Entity {
public:
    Entity();

    virtual void render();

    virtual void set_pos(vec2f_t new_pos)
    {
        position = new_pos;
        update_render_position();
    }
    virtual void set_rot(double new_rot) { rotation = new_rot; }
    virtual void set_hidden(bool hide = true) { hidden = hide; }

    virtual void add_child(Entity* node)
    {
        if (node) {
            children.push_back(node);
        }
    }

    bool is_hidden() const { return hidden; }
    vec2f_t pos() const { return position; }
    double rot() const { return rotation; }

protected:
    void update_render_position();

    std::vector<Entity*> children;

    vec2f_t position;
    double rotation = 0.0f; // rotation in degrees

    bool hidden = false;

    SDL_Texture* tex = nullptr;
    SDL_Rect tex_src = {0};
    SDL_Rect draw_dest = {0};
    SDL_Point rot_pivot = {0};
};
#endif
