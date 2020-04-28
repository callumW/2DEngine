#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "Entity.h"
#include "entity_id.h"

#include <array>
#include <utility>
#include <vector>

class EntityManager {
public:
    static EntityManager& get();

    Entity* find_entity(entity_id_t id);

    std::pair<entity_id_t, Entity*> new_entity();

    void update_dirty_entities(float delta);
    void update_all_entities(float delta);


    void render_entities();

private:
    EntityManager() = default;

    size_t next_free_space = 0;
    std::array<Entity, MAX_NUM_ENTITIES> entities;
};

#endif
