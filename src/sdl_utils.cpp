#include "sdl_utils.h"

std::ostream& operator<<(std::ostream& str, SDL_Rect const& rect)
{
    str << "{" << rect.x << ", " << rect.y << " | " << rect.w << "x" << rect.h << "}";
    return str;
}
