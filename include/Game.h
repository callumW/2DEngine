#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>

#include "Entity.h"
#include "game_math.h"

class Game {
public:
    Game();
    ~Game();

    void render();

    void update(Uint32 delta);
};
#endif
