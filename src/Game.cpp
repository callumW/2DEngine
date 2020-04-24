#include "Game.h"
#include "Globals.h"
#include "game_math.h"
#include "input.h"
#include "loading_helpers.h"

#include <cmath>
#include <iostream>


Game::Game()
{
    Entity* tmp = new Entity();

    tmp->set_local_pos({10.0f, 10.0f});

    entity.add_child(tmp);

    entity.add_force({10.0f, 10.0f});
    tmp->add_force({10.0f, 10.0f});
}

Game::~Game()
{
    if (m_player_tex) {
        SDL_DestroyTexture(m_player_tex);
    }
}

void Game::render()
{
    player.render();
    entity.render();
}

void Game::update(Uint32 delta)
{
    float delta_f = static_cast<float>(delta) / 1000.0f;
    player.update(delta_f);
    entity.update(delta_f);
}
