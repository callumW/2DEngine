#include "EntityManager.h"
#include "PhysicsManager.h"

#include <algorithm>
#include <cassert>
#include <iostream>

EntityManager::EntityManager()
{
    entities.resize(NUM_OF_ENTITIES);
    std::cout << "EntityManager address: " << (void*) this << std::endl;
}

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
    new_id.set_index(next_free_space);
    new_id.set_generation(entities[next_free_space].id.generation());
    entities[next_free_space].id = new_id;
    next_free_space++;

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
        std::cout << "Scheduling destructor for: " << id << std::endl;
        marked_for_death.insert(id);
    }
    else {
        std::cout << "Not schedule_destruction as entity " << id << " does not exist" << std::endl;
    }
}

void EntityManager::process_dead_entities()
{
    std::for_each(marked_for_death.begin(), marked_for_death.end(),
                  std::bind(&EntityManager::destroy_entity, this, std::placeholders::_1));
    marked_for_death.clear();
}

void EntityManager::destroy_entity(entity_id_t const& e)
{
    std::cout << "EntityManager: Destoying entity: " << e << std::endl;
    entities[e.index()].reset();
    entities[e.index()].id.increment_generation();

    dead_entities.insert(e);

    if (next_free_space > 1 && e.index() != next_free_space - 1) {
        // setup swap record
        entity_id_pair_t swapped_pair;
        swapped_pair.first = entities[next_free_space - 1].id;
        swapped_pair.second = swapped_pair.first;
        swapped_pair.second.set_index(e.index());

        moved_entities.insert(swapped_pair);

        std::cout << "Adding moved record: " << swapped_pair.first.index() << "->"
                  << swapped_pair.second.index() << std::endl;

        std::swap(entities[swapped_pair.second.index()], entities[swapped_pair.first.index()]);

        entities[swapped_pair.second.index()].id = swapped_pair.second;

        std::cout << swapped_pair.first << " vs. " << entities[swapped_pair.second.index()].id
                  << std::endl;

        assert(swapped_pair.first.generation() ==
               entities[swapped_pair.second.index()].id.generation());

        entities[next_free_space - 1].id.set_index(next_free_space - 1);
    }
    next_free_space--;
}
