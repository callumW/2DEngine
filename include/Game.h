#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>

#include <array>

#include "Entity.h"
#include "Player.h"
#include "game_math.h"

class Game {
public:
    Game();
    ~Game();

    void render();

    void update(Uint32 delta);

private:
    std::array<Entity, 50000> entities;
    Player player;
};
#endif
