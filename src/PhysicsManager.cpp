#include "PhysicsManager.h"
#include "EntityManager.h"
#include "Globals.h"

#include <iostream>

PhysicsManager::PhysicsManager() {}

PhysicsManager& PhysicsManager::get()
{
    static PhysicsManager phys_mgr;
    return phys_mgr;
}

void PhysicsManager::simulate(float delta)
{
    dirty_components.clear();

    check_for_dead_entities();
    check_for_moved_entities();

    size_t comp_count = physics_components.size();
    for (size_t i = 0; i < comp_count; i++) {
        physics_component_t& comp = physics_components[i];
        if (comp.net_force != vec2f_t::zero()) {
            comp.position += comp.net_force * delta;
            dirty_components.push_back(comp.owner_id);
        }
    }
}

physics_component_t* PhysicsManager::new_physics_component(entity_id_t id)
{
    assert(map.find(id) == map.end());

    physics_component_t comp;
    comp.owner_id = id;
    physics_components.push_back(comp);

    auto idx = physics_components.size() - 1;

    map.insert({id, idx});

    return &physics_components[idx];
}

physics_component_t const* PhysicsManager::get_physics_component(entity_id_t id)
{
    physics_component_t const* ret = nullptr;
    auto const res = map.find(id);
    if (res != map.end()) {
        ret = &physics_components[res->second];
    }
    return ret;
}

void PhysicsManager::check_for_dead_entities()
{
    auto const& dead_list = EntityManager::get().get_dead_set();

    // TODO check that the removed entity actually has a physics component?
    for (auto& e : dead_list) {
        if (physics_components.size() > 1) {
            std::cout << "swap path, num components: " << physics_components.size() << std::endl;

            // locate removed entity
            auto dead_location = map.find(e);
            assert(dead_location != map.end());
            size_t const dead_idx = dead_location->second;

            // erase removed entity from entitiy_id -> component map
            map.erase(dead_location);

            // swap removed entity with valid entity add end of vector
            std::swap(physics_components[dead_idx],
                      physics_components[physics_components.size() - 1]);

            // remove component of removed entity
            physics_components.pop_back();

            // update
            auto moved_ent_id = physics_components[dead_idx].owner_id;

            map[moved_ent_id] = dead_idx;

            std::cout << "Size after removal: " << physics_components.size() << std::endl;
        }
        else {
            std::cout << "popping back" << std::endl;
            physics_components.pop_back();
            map.erase(e);
        }
    }
}

void PhysicsManager::check_for_moved_entities()
{
    auto const& moved_ents = EntityManager::get().get_moved_set();

    for (auto& pair : moved_ents) {
        auto old_id = pair.first;
        auto new_id = pair.second;

        update_entity_mapping(old_id, new_id);
    }
}

void PhysicsManager::update_entity_mapping(entity_id_t const& old_id, entity_id_t const& new_id)
{
    std::cout << "Updating entity " << old_id.index() << " -> " << new_id.index() << std::endl;
    // update id in vector
    auto find_result = map.find(old_id);

    // TODO check that entity has component
    assert(find_result != map.end());

    size_t component_pos = find_result->second;

    physics_components[component_pos].owner_id = new_id;

    // update mapping
    map.erase(find_result);
    map[new_id] = component_pos;
}
