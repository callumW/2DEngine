#include "Game.h"
#include "EntityManager.h"
#include "Globals.h"
#include "InputSystem.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "TimingSystem.h"
#include "UISystem.h"
#include "file_utils.h"
#include "game_math.h"
#include "input.h"
#include "loading_helpers.h"

#include <json/json.h>
#include <tmx.h>

#include <cmath>
#include <iostream>
#include <utility>


Game::Game() { RenderManager::get().enable_grid(true, 0, 0, 255, 126, 64, 64); }

void Game::render() { RenderManager::get().render_all(); }

void Game::update(Uint32 delta)
{
    float delta_f = static_cast<float>(delta) / 1000.0f;
    TimingSystem::get().update(delta_f);

    RenderManager::get().update_animations(delta_f);
    InputSystem::get().update();
}
