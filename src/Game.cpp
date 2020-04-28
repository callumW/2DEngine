#include "Game.h"
#include "Globals.h"
#include "game_math.h"
#include "input.h"
#include "loading_helpers.h"

#include <cmath>
#include <iostream>


Game::Game()
{
    bool toggle = true;
    for (auto& e : entities) {
        if (toggle) {
            e.add_force({10.0f, 10.0f});
        }
        toggle = !toggle;
    }
}

Game::~Game() {}

void Game::render()
{
    player.render();
    for (auto& e : entities) {
        e.render();
    }
}

void Game::update(Uint32 delta)
{
    float delta_f = static_cast<float>(delta) / 1000.0f;
    player.update(delta_f);
    for (auto& e : entities) {
        e.update(delta_f);
    }
}
