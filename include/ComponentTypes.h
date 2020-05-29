#ifndef COMPONENT_TYPES_H
#define COMPONENT_TYPES_H

#include <cstdint>

typedef int64_t COMPONENT_TYPE;

static constexpr COMPONENT_TYPE RENDER = 1 << 0;
static constexpr COMPONENT_TYPE PHYSICS = 1 << 1;
static constexpr COMPONENT_TYPE ANIMATION = 1 << 2;

#endif
