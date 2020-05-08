#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "Entity.h"

#include <functional>

/**
 *  y
 * x +--------+
 *   |        |
 *   |        |   h
 *   |        |
 *   +--------+
 *        w
 */
typedef struct aabb_t {
    float x = 0.0f;
    float y = 0.0f;
    float w = 0.0f;
    float h = 0.0f;

    aabb_t(float xx, float yy, float ww, float hh)
    {
        x = xx;
        y = yy;
        w = ww;
        h = hh;
    }
    aabb_t() : aabb_t(0.0f, 0.0f, 0.0f, 0.0f){};
} aabb_t;

bool aabb_test_collision(aabb_t const& lhs, aabb_t const& rhs);

typedef struct collision_component_t {
    aabb_t box = {};
    std::function<void(collision_component_t const&)> on_collide = {};
} collision_component_t;
#endif
