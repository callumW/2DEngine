#ifndef ANIMATION_H
#define ANIMATION_H
#include <ostream>
#include <vector>

#include "Texture.h"

typedef struct animation_frame_t {
    texture_t texture;
    float duration = 1.0f;
} animation_frame_t;

typedef struct animation_t {
    std::vector<animation_frame_t> frames = {};
    float cur_time = 0.0f;
    float total_duration = 0.0f;
    size_t cur_pos = 0;
} animation_t;

std::ostream& operator<<(std::ostream& str, animation_frame_t const& frame);

#endif
