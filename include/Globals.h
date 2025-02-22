#ifndef GLOBALS_H
#define GLOBALS_H
#include <SDL2/SDL.h>

extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;

extern int const WINDOW_WIDTH;
extern int const WINDOW_HEIGHT;

size_t const NUM_OF_ENTITIES = 1000;

bool const SHOW_COLLISION_DEBUG = true;

float const RENDER_SCALE_FACTOR = 100.0f;
#endif
