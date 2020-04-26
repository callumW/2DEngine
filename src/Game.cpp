#include "Game.h"
#include "Globals.h"
#include "game_math.h"
#include "input.h"
#include "loading_helpers.h"

#include <cmath>
#include <iostream>


Game::Game()
{
    Player* player = new Player();
    root_node.add_child(player);
}

Game::~Game() {}

void Game::render() { root_node.render(); }

void Game::update(Uint32 delta)
{
    float delta_f = static_cast<float>(delta) / 1000.0f;
    root_node.update(delta_f);
}
