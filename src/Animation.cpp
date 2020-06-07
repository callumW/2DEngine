#include "Animation.h"

std::ostream& operator<<(std::ostream& str, animation_frame_t const& frame)
{
    str << "Texture: " << frame.texture << " | " << frame.duration << "s";

    return str;
}
