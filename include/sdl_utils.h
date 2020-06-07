#ifndef SDL_UTILS_H
#define SDL_UTILS_H
#include <SDL2/SDL.h>
#include <ostream>


std::ostream& operator<<(std::ostream& str, SDL_Rect const& rect);
#endif
