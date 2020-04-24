#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game {
public:
    Game();

    void render_to(SDL_Surface* surface);

    void update(Uint32 delta);

private:
    SDL_Surface* game_surface = nullptr;
    SDL_Surface* player_surface = nullptr;
    SDL_Rect player_rect = {};

    float player_pos[2] = {0.0f};
};
#endif
