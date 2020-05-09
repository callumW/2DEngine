#include "CollisionSystem.h"
#include <iostream>

#include "PhysicsManager.h"


CollisionSystem& CollisionSystem::get()
{
    static CollisionSystem system;
    return system;
}

void CollisionSystem::check_for_collisions()
{
    for (auto& pair : PhysicsManager::get().get_dirty_positions()) {
        entity_t const& entity = pair.first;
        vec2f_t* new_pos = pair.second;

        if (entity.has_component(COLLISION)) {
            auto find_res = map.find(entity);
            assert(find_res != map.end());

            size_t pos = find_res->second;

            collision_component_t& collision_comp = components[pos];
            collision_comp.box.x = new_pos->x;
            collision_comp.box.y = new_pos->y;

            size_t size = components.size();
            for (size_t i = 0; i < size; i++) {
                if (i != pos) {
                    auto const& other_collider = components[i];
                    // move back where it came from?
                    if (aabb_test_collision(other_collider.box, collision_comp.box)) {
                        std::cout << "Collision" << std::endl;
                        if (collision_comp.on_collide) {
                            collision_comp.on_collide(other_collider);
                        }
                        new_pos->y = other_collider.box.y - collision_comp.box.h;
                        collision_comp.box.y = new_pos->y;
                    }
                }
            }
        }
        else {
            std::cout << "No collision component, collision: " << entity.components << std::endl;
        }
    }
}
