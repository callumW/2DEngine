#ifndef GAME_H
#define GAME_H
#include <array>

#include <SDL2/SDL.h>
#include <box2d/box2d.h>

#include "game_math.h"


class Game {
public:
    Game();
    ~Game() = default;

    void render();

    void update(Uint32 delta);

private:
    void spawn_ball(vec2f_t const& position);

    void load_map();

    b2Vec2 gravity = {0.0f, -10.0f};
    b2World world;
};
#endif
