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
    Entity() = default;

    virtual void update(float delta);

    /**
     * Change position local to parent
     */
    virtual void set_local_transform(transform_t const& transform);

    /**
     * Change position in world space (irrelevant of parent position)
     */
    virtual void set_world_transform(transform_t const& transform);

    virtual void face(Entity const& entity);
    virtual void face(vec2f_t const& vec);

    virtual void recalc_local_transform();
    virtual void recalc_world_transform();

    entity_id_t id;

    transform_t local_transform;
    transform_t world_transform;
};
#endif
