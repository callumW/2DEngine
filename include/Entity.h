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

    void update(float delta);

    /**
     * Change position local to parent
     */
    void set_local_transform(transform_t const& transform);

    /**
     * Change position in world space (irrelevant of parent position)
     */
    void set_world_transform(transform_t const& transform);

    void face(Entity const& entity);
    void face(vec2f_t const& vec);

    inline void recalc_local_transform() { local_transform = world_transform; }

    inline void recalc_world_transform() { world_transform = local_transform; }

    entity_id_t id;

    transform_t local_transform;
    transform_t world_transform;
};
#endif
