#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>

#include <string>
#include <vector>

#include "entity_id.h"
#include "game_math.h"

class EntityManager;

class Entity {
public:
    Entity();

    Entity(std::string const& texture_path, SDL_Rect const& src);

    virtual void render();
    virtual void update(float delta);

    /**
     * Change position local to parent
     */
    virtual void set_local_transform(transform_t const& transform);

    /**
     * Change position in world space (irrelevant of parent position)
     */
    virtual void set_world_transform(transform_t const& transform);

    virtual void set_hidden(bool hide = true) { hidden = hide; }

    // Add forces, NOTE: forces are in WORLD coordinate space
    virtual void set_force(vec2f_t new_force) { force = new_force; }
    virtual void add_force(vec2f_t add) { force += add; }

    virtual void add_child(Entity* node);

    virtual void remove_child(Entity* node);

    virtual void remove_from_parent();

    virtual void face(Entity const& entity);
    virtual void face(vec2f_t const& vec);

    void reset(){};

    bool is_hidden() const { return hidden; }

    void apply_forces(float const delta_time);

    virtual void recalc_local_transform();
    virtual void recalc_world_transform();

    virtual void update_children_world_transforms();

    entity_id_t id;

    std::vector<entity_id_t> children;
    entity_id_t parent;

    transform_t local_transform;
    transform_t world_transform;

    bool hidden = false;

    SDL_Texture* tex = nullptr;
    SDL_Rect tex_src = {0};
    SDL_Rect draw_dest = {0};
    SDL_Point rot_pivot = {0};

    vec2f_t force = {0.0f, 0.0f};
};
#endif
