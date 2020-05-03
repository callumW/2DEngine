#include "InputSystem.h"
#include "input.h"

#include <iostream>

InputSystem& InputSystem::get()
{
    static InputSystem sys;
    return sys;
}

void InputSystem::update()
{
    if (INPUT.mouse_left_click) {
        mouse_left_was_down = true;
    }
    else if (!INPUT.mouse_left_click && mouse_left_was_down) {
        mouse_left_was_down = false;
        left_click({static_cast<float>(INPUT.mouse_x), static_cast<float>(INPUT.mouse_y)});
    }
}

void InputSystem::left_click(vec2f_t const& loc)
{
    for (auto& callback : on_mouse_left_click_callbacks) {
        callback(loc);
    }
}
