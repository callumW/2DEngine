#include "Game.h"
#include "CollisionSystem.h"
#include "Globals.h"
#include "InputSystem.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "TimingSystem.h"
#include "UISystem.h"
#include "game_math.h"
#include "input.h"
#include "loading_helpers.h"

#include <cmath>
#include <iostream>

float const PLAYER_MOVEMENT_SPEED = 250.0f;
float const PLAYER_BULLET_SPEED = 1000.0f;
float const PLAYER_FIRE_RATE = 1.0f / 10.0f;


Game::Game() {}

Game::~Game() {}

void Game::render() {}

void Game::update(Uint32 delta) { float delta_f = static_cast<float>(delta) / 1000.0f; }
