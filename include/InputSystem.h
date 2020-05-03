#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "game_math.h"

#include <functional>
#include <vector>


class InputSystem {
public:
    typedef std::function<void(vec2f_t const&)> mouse_click_callback_t;

    void on_mouse_left_click(mouse_click_callback_t cb)
    {
        if (cb) {
            on_mouse_left_click_callbacks.push_back(cb);
        }
    }

    void update();

    static InputSystem& get();

private:
    InputSystem() = default;

    void left_click(vec2f_t const& loc);

    std::vector<mouse_click_callback_t> on_mouse_left_click_callbacks;

    bool mouse_left_was_down = false;
};
#endif
