#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>

#include "game_math.h"

class Entity {
public:
    Entity();

    virtual void render();

    virtual void set_pos(vec2f_t new_pos) { position = new_pos; }
    virtual void set_rot(double new_rot) { rotation = new_rot; }
    virtual void set_hidden(bool hide = true) { hide = hidden; }

protected:
    vec2f_t position;
    double rotation = 0.0f; // rotation in degrees

    bool hidden = false;

    SDL_Texture* tex = nullptr;
    SDL_Rect tex_src = {0};
    SDL_Rect draw_dest = {0};
    SDL_Point rot_pivot = {0};
};
#endif
