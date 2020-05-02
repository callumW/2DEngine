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

            // locate removed entity
            auto dead_location = map.find(e);
            if (dead_location == map.end()) {
                continue;
            }
            size_t const dead_idx = dead_location->second;

            // erase removed entity from entitiy_id -> component map
            map.erase(dead_location);

            if (dead_idx < physics_components.size() - 1) {

                // swap removed entity with valid entity add end of vector
                std::swap(physics_components[dead_idx],
                          physics_components[physics_components.size() - 1]);

                // remove component of removed entity
                physics_components.pop_back();

                // update
                auto moved_ent_id = physics_components[dead_idx].owner_id;

                map[moved_ent_id] = dead_idx;
            }
            else {
                physics_components.pop_back();
            }
        }
        else {
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
    // update id in vector
    auto find_result = map.find(old_id);

    if (find_result == map.end()) {
        return;
    }

    size_t component_pos = find_result->second;

    physics_components[component_pos].owner_id = new_id;

    // update mapping
    map.erase(find_result);
    map[new_id] = component_pos;

    verify_removed(old_id);
    validate_map();
}

void PhysicsManager::log_map()
{
    std::cout << "Current entities w/ physics components: " << std::endl;
    for (auto const& ele : map) {
        std::cout << "\t" << ele.first << "->" << ele.second << std::endl;
    }
}

void PhysicsManager::cleanup()
{
    check_for_dead_entities();
    check_for_moved_entities();
}

void PhysicsManager::validate_map()
{
    // verify no duplicate (or cross-generation) entities in map

    for (auto it = map.begin(); it != map.end(); it++) {
        for (auto inner_it = map.begin(); inner_it != map.end(); inner_it++) {
            if (it->first.index() == inner_it->first.index() && it != inner_it) {
                std::cout << "Duplicate detected: " << it->first << " vs. " << inner_it->first
                          << std::endl;
                exit(1);
            }
        }
    }
}

void PhysicsManager::verify_removed(entity_id_t const& id)
{
    for (auto it = map.begin(); it != map.end(); it++) {
        if (it->first.index() == id.index()) {
            std::cout << id << " was not removed: " << it->first << std::endl;
            exit(1);
        }
    }
}
