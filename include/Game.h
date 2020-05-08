#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <array>

#include "game_math.h"


class Game {
public:
    Game();
    ~Game() = default;

    void render();

    void update(Uint32 delta);

private:
    void spawn_ball(vec2f_t const& position);
};
#endif
