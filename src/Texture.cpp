#include "Texture.h"
#include "sdl_utils.h"

std::ostream& operator<<(std::ostream& str, texture_t const& tex)
{
    str << "src_rect: " << tex.src_rect;
    return str;
}
