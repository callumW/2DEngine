#include "CollisionComponent.h"

bool aabb_test_collision(aabb_t const& lhs, aabb_t const& rhs)
{
    return (lhs.x < rhs.x + rhs.w && lhs.x + lhs.w > rhs.x && lhs.y < rhs.y + rhs.h &&
            lhs.y + lhs.h > rhs.y);
}
