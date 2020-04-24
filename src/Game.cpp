#include "Game.h"
#include "input.h"

float const PLAYER_MOVEMENT_SPEED = 250.0f; // pixels per second

Game::Game() { player_surface = SDL_LoadBMP("./assets/G.bmp"); }

void Game::render_to(SDL_Surface* surface)
{
    if (player_surface && surface) {
        SDL_BlitSurface(player_surface, nullptr, surface, &player_rect);
    }
}

void Game::update(Uint32 delta)
{
    float delta_f = static_cast<float>(delta) / 1000.0f;
    if (INPUT.KEY_W) {
        player_pos[1] -= PLAYER_MOVEMENT_SPEED * delta_f;
    }
    else if (INPUT.KEY_S) {
        player_pos[1] += PLAYER_MOVEMENT_SPEED * delta_f;
    }

    if (INPUT.KEY_A) {
        player_pos[0] -= PLAYER_MOVEMENT_SPEED * delta_f;
    }
    else if (INPUT.KEY_D) {
        player_pos[0] += PLAYER_MOVEMENT_SPEED * delta_f;
    }

    player_rect.x = static_cast<Sint32>(player_pos[0]);
    player_rect.y = static_cast<Sint32>(player_pos[1]);
}
