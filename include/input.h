#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

typedef struct input_t {
    bool KEY_W = false;
    bool KEY_A = false;
    bool KEY_S = false;
    bool KEY_D = false;
    bool KEY_SHIFT = false;
    bool KEY_SPACE = false;

    Sint32 mouse_x = 0;
    Sint32 mouse_y = 0;

    bool mouse_right_click = false;
    bool mouse_left_click = false;
} input_t;

extern input_t INPUT; // main input object

void update_input_struct(SDL_Event const& e);
#endif
