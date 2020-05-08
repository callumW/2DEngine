#include "CollisionSystem.h"

#include "PhysicsManager.h"

void CollisionSystem::check_for_collisions()
{
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
