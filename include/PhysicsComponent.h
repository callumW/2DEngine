#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "entity_id.h"
#include "game_math.h"

typedef struct physics_component_t {
    entity_id_t owner_id;
    vec2f_t position;
    vec2f_t net_force;
} physics_component_t;
#endif
