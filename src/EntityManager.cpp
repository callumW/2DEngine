#include "EntityManager.h"

#include <cassert>


Entity* EntityManager::is_alive(entity_id_t id)
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

    return std::make_pair(new_id, &entities[new_id.index()]);
}

// void EntityManager::free()
// {
//     assert(next_free_space > 0);
//     std::swap
// }

void EntityManager::update_entities(float delta)
{
    for (size_t i = 0; i < next_free_space; i++) {
        entities[i].update(delta);
    }
}

void EntityManager::render_entities()
{
    for (size_t i = 0; i < next_free_space; i++) {
        entities[i].render();
    }
}

EntityManager& EntityManager::get()
{
    static EntityManager entity_manager;
    return entity_manager;
}
