#include "Game.h"
#include "EntityManager.h"
#include "Globals.h"
#include "RenderManager.h"
#include "game_math.h"
#include "input.h"
#include "loading_helpers.h"

#include <cmath>
#include <iostream>


Game::Game()
{
    auto new_entity = EntityManager::get().new_entity();
    new_entity.second->add_force({10.0f, 10.0f});

    auto render_comp = RenderManager::get().new_render_component();
    render_comp->entity_id = new_entity.first;
    render_comp->hidden = false;
    render_comp->texture = load_default_texture();
    render_comp->src_rect.w = 40;
    render_comp->src_rect.h = 40;
    render_comp->dst_rect = render_comp->src_rect;
    render_comp->pivot_point = {20, 20};
}

Game::~Game() {}

void Game::render() { RenderManager::get().render_all(); }

void Game::update(Uint32 delta)
{
    float delta_f = static_cast<float>(delta) / 1000.0f;

    EntityManager::get().update_entities(delta_f);
}
