#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "Entity.h"
#include "game_math.h"

typedef struct physics_component_t {
    vec2f_t position = {};
    vec2f_t net_force = {};
    bool is_affected_by_gravity = false;
} physics_component_t;
#endif
