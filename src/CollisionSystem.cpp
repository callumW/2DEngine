#include "CollisionSystem.h"

#include "EntityManager.h"
#include "PhysicsManager.h"


CollisionSystem& CollisionSystem::get()
{
    static CollisionSystem sys;
    return sys;
}

void CollisionSystem::check_for_collisions()
{

    // check for updates
    update_dirty_colliders();

    for (auto it = components.begin(); it != components.end(); it++) {
        for (auto other_it = components.begin(); other_it != components.end(); other_it++) {
            if (it != other_it) {
                if (aabb_test_collision(it->box, other_it->box)) {
                    if (it->on_collide) {
                        it->on_collide(*other_it);
                    }
                }
            }
        }
    }
}

collision_component_t* CollisionSystem::new_collision_component(entity_id_t const& id)
{
    assert(map.find(id) == map.end());

    collision_component_t comp = {};
    comp.owner_id = id;
    components.push_back(comp);

    auto idx = components.size() - 1;

    map.insert({id, idx});

    return &components[idx];
}

collision_component_t* CollisionSystem::get_collision_component(entity_id_t const& id)
{
    collision_component_t* ret = nullptr;
    auto const res = map.find(id);
    if (res != map.end()) {
        ret = &components[res->second];
    }
    return ret;
}

void CollisionSystem::check_for_moved_entities()
{
    auto const& moved_ents = EntityManager::get().get_moved_set();

    for (auto& pair : moved_ents) {
        auto old_id = pair.first;
        auto new_id = pair.second;

        update_entity_mapping(old_id, new_id);
    }
}

void CollisionSystem::update_entity_mapping(entity_id_t const& old_id, entity_id_t const& new_id)
{
    // update id in vector
    auto find_result = map.find(old_id);

    if (find_result == map.end()) {
        return;
    }

    size_t component_pos = find_result->second;

    components[component_pos].owner_id = new_id;

    // update mapping
    map.erase(find_result);
    map[new_id] = component_pos;

    verify_removed(old_id);
    validate_map();
}

void CollisionSystem::check_for_dead_entities()
{
    auto const& dead_list = EntityManager::get().get_dead_set();

    // TODO check that the removed entity actually has a physics component?
    for (auto& e : dead_list) {
        if (components.size() > 1) {

            // locate removed entity
            auto dead_location = map.find(e);
            if (dead_location == map.end()) {
                continue;
            }
            size_t const dead_idx = dead_location->second;

            // erase removed entity from entitiy_id -> component map
            map.erase(dead_location);

            if (dead_idx < components.size() - 1) {

                // swap removed entity with valid entity add end of vector
                std::swap(components[dead_idx], components[components.size() - 1]);

                // remove component of removed entity
                components.pop_back();

                // update
                auto moved_ent_id = components[dead_idx].owner_id;

                map[moved_ent_id] = dead_idx;
            }
            else {
                components.pop_back();
            }
        }
        else {
            components.pop_back();
            map.erase(e);
        }
    }
}

void CollisionSystem::cleanup()
{
    check_for_dead_entities();
    check_for_moved_entities();
}

void CollisionSystem::validate_map()
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

void CollisionSystem::verify_removed(entity_id_t const& id)
{
    for (auto it = map.begin(); it != map.end(); it++) {
        if (it->first.index() == id.index()) {
            std::cout << id << " was not removed: " << it->first << std::endl;
            exit(1);
        }
    }
}

void CollisionSystem::update_dirty_colliders()
{
    auto dirty_entities = PhysicsManager::get().dirty_entities();

    for (auto dirty : dirty_entities) {
        auto collider = get_collision_component(dirty);
        if (collider) {
            auto entity = EntityManager::get().find_entity(dirty);
            assert(entity != nullptr);

            collider->box.x = entity->world_transform.position.x;
            collider->box.y = entity->world_transform.position.y;
        }
    }
}
