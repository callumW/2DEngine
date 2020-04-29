#include "EntityManager.h"
#include "PhysicsManager.h"

#include <cassert>

EntityManager::EntityManager() { entities.resize(1000000); }

Entity* EntityManager::find_entity(entity_id_t id)
{
    assert(id.index() < MAX_NUM_ENTITIES);
    Entity* tmp = nullptr;
    if (id.generation() == entities[id.index()].id.generation()) {
        tmp = &entities[id.index()];
    }
    return tmp;
}

std::pair<entity_id_t, Entity*> EntityManager::new_entity()
{
    assert(next_free_space < MAX_NUM_ENTITIES);
    entity_id_t new_id;
    new_id.set_index(next_free_space++);
    new_id.increment_generation();
    entities[new_id.index()].id = new_id;

    return std::make_pair(new_id, &entities[new_id.index()]);
}

void EntityManager::update_dirty_entities(float delta)
{
    for (auto const& dirty_entity : PhysicsManager::get().dirty_entities()) {
        assert(dirty_entity.index() < next_free_space);
        entities[dirty_entity.index()].update(delta);
    }
}

void EntityManager::update_all_entities(float delta)
{
    for (size_t i = 0; i < next_free_space; i++) {
        entities[i].update(delta);
    }
}

EntityManager& EntityManager::get()
{
    static EntityManager entity_manager;
    return entity_manager;
}
