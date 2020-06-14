#include "input.h"

#include <iostream>

input_t INPUT = {};


inline void update_key(bool down, SDL_Keycode const& code)
{
    switch (code) {
        case SDLK_w:
            INPUT.KEY_W = down;
            break;
        case SDLK_a:
            INPUT.KEY_A = down;
            break;
        case SDLK_s:
            INPUT.KEY_S = down;
            break;
        case SDLK_d:
            INPUT.KEY_D = down;
            break;
        case SDLK_LSHIFT:
        case SDLK_RSHIFT:
            INPUT.KEY_SHIFT = down;
            break;
        case SDLK_SPACE:
            INPUT.KEY_SPACE = down;
            break;
    }
}

inline void update_mouse_pos(SDL_MouseMotionEvent const& motion_event)
{
    INPUT.mouse_x = motion_event.x;
    INPUT.mouse_y = motion_event.y;
    // std::cout << "Updated mouse pos to: " << INPUT.mouse_x << "x" << INPUT.mouse_y << std::endl;
}

inline void update_mouse_buttons(bool down, SDL_MouseButtonEvent const& button_event)
{
    if (button_event.button == SDL_BUTTON_LEFT) {
        INPUT.mouse_left_click = down;
        // std::cout << "left mouse: " << (down ? "down" : "up") << std::endl;
    }
    else if (button_event.button == SDL_BUTTON_RIGHT) {
        INPUT.mouse_right_click = down;
        // std::cout << "right mouse: " << (down ? "down" : "up") << std::endl;
    }
}

void update_input_struct(SDL_Event const& e)
{
    switch (e.type) {
        case SDL_KEYDOWN:
            update_key(true, e.key.keysym.sym);
            break;
        case SDL_KEYUP:
            update_key(false, e.key.keysym.sym);
            break;
        case SDL_MOUSEMOTION:
            update_mouse_pos(e.motion);
            break;
        case SDL_MOUSEBUTTONDOWN:
            update_mouse_buttons(true, e.button);
            break;
        case SDL_MOUSEBUTTONUP:
            update_mouse_buttons(false, e.button);
            break;
    }
}
