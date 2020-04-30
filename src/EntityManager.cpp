#include "EntityManager.h"
#include "PhysicsManager.h"

#include <algorithm>
#include <cassert>

EntityManager::EntityManager() { entities.resize(NUM_OF_ENTITIES); }

Entity* EntityManager::find_entity(entity_id_t id)
{
    assert(id.index() < MAX_NUM_ENTITIES);
    Entity* tmp = nullptr;
    if (has_entity(id)) {
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


EntityManager& EntityManager::get()
{
    static EntityManager entity_manager;
    return entity_manager;
}

void EntityManager::schedule_destruction(entity_id_t const id)
{
    if (has_entity(id)) {
        dead_entities.insert(id);
    }
}

void EntityManager::process_dead_entities()
{
    std::for_each(dead_entities.begin(), dead_entities.end(),
                  std::bind(&EntityManager::destroy_entity, this, std::placeholders::_1));
    dead_entities.clear();
}

void EntityManager::destroy_entity(entity_id_t const& e)
{
    entities[e.index()].reset();
    entities[e.index()].id.increment_generation();
}
