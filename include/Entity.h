#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>

#include <string>
#include <vector>

#include "SceneNode.h"
#include "game_math.h"

class Entity : public SceneNode {
public:
    Entity();

    Entity(std::string const& texture_path, SDL_Rect const& src);

    virtual void update(float delta);

    virtual void render();

    // Add forces, NOTE: forces are in WORLD coordinate space
    virtual void set_force(vec2f_t new_force) { force = new_force; }
    virtual void add_force(vec2f_t add) { force += add; }

    virtual void face(Entity const& entity);
    virtual void face(vec2f_t const& vec);

protected:
    void apply_forces(float const delta_time);

    SDL_Texture* tex = nullptr;
    SDL_Rect tex_src = {0};
    SDL_Rect draw_dest = {0};
    SDL_Point rot_pivot = {0};

    vec2f_t force = {0.0f, 0.0f};
};

#endif
