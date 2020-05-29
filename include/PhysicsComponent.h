#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H
#include <box2d/box2d.h>

#include "Entity.h"
#include "game_math.h"

typedef struct physics_component_t {
    b2Body* body = nullptr;
} physics_component_t;
#endif
