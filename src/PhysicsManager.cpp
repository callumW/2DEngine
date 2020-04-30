#include "PhysicsManager.h"
#include "EntityManager.h"
#include "Globals.h"

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

    for (auto& e : dead_list) {
        if (physics_components.size() > 1) {
            // swap end and removed
            auto dead_location = map.find(e);
            assert(dead_location != map.end());
            size_t const dead_idx = dead_location->second;

            map.erase(dead_location);

            std::swap(physics_components[dead_idx],
                      physics_components[physics_components.size() - 1]);
            physics_components.pop_back();

            auto const& moved_ent_id = physics_components[dead_idx].owner_id;

            map[moved_ent_id] = dead_idx;
        }
    }
}
