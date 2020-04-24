#include "Game.h"
#include "input.h"

#include <iostream>

float const PLAYER_MOVEMENT_SPEED = 250.0f; // pixels per second

Game::Game(SDL_Renderer* renderer, int win_width, int win_height) :
    m_renderer(renderer),
    m_window_width(win_width),
    m_window_height(win_height)
{
    SDL_Surface* tmp = SDL_LoadBMP("./assets/G.bmp");

    if (tmp) {
        m_player_tex = SDL_CreateTextureFromSurface(m_renderer, tmp);
        if (m_player_tex == nullptr) {
            std::cout << "Failed to load player texture" << std::endl;
        }

        SDL_FreeSurface(tmp);
    }

    player_rect.w = 40;
    player_rect.h = 40;
}

Game::~Game()
{
    if (m_player_tex) {
        SDL_DestroyTexture(m_player_tex);
    }
}

void Game::render()
{
    if (m_renderer && m_player_tex) {
        SDL_RenderCopy(m_renderer, m_player_tex, nullptr, &player_rect);
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
