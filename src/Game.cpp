#include "Game.h"
#include "input.h"
#include "loading_helpers.h"
#include "math_helpers.h"

#include <cmath>
#include <iostream>

float const PLAYER_MOVEMENT_SPEED = 250.0f; // pixels per second

Game::Game(SDL_Renderer* renderer, int win_width, int win_height) :
    m_renderer(renderer),
    m_window_width(win_width),
    m_window_height(win_height)
{
    m_player_tex = load_texture("./assets/G.bmp", m_renderer);
    if (m_player_tex == nullptr) {
        std::cout << "Failed to load player texture" << std::endl;
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
        SDL_RenderCopyEx(m_renderer, m_player_tex, nullptr, &player_rect, player_rotation, nullptr,
                         SDL_FLIP_NONE);
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

    player_rect.x = static_cast<Sint32>(player_pos[0] - 20.0f);
    player_rect.y = static_cast<Sint32>(player_pos[1] - 20.0f);

    float mouse_x = static_cast<float>(INPUT.mouse_x);
    float mouse_y = static_cast<float>(INPUT.mouse_y);

    float rot = rad_to_degrees(atan2((mouse_y - player_pos[1]), (mouse_x - player_pos[0])));

    player_rotation = static_cast<double>(rot);
}
