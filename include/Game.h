#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>

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
    SDL_Texture* m_player_tex = nullptr;
    SDL_Rect player_rect = {};

    vec2f_t player_pos = {0.0f, 0.0f};
    double player_rotation = 0.0f;

    Entity entity;
    Player player;
};
#endif
