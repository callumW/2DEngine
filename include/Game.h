#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game {
public:
    Game(SDL_Renderer* renderer, int win_width, int win_height);
    ~Game();

    void render();

    void update(Uint32 delta);

private:
    SDL_Renderer* m_renderer = nullptr;

    int m_window_width = 0;
    int m_window_height = 0;


    SDL_Texture* m_player_tex = nullptr;
    SDL_Rect player_rect = {};

    float player_pos[2] = {0.0f};
};
#endif
