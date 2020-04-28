#include "Entity.h"
#include "Globals.h"
#include "PhysicsManager.h"
#include "loading_helpers.h"

#include <cassert>
#include <cmath>
#include <iostream>


void Entity::update(float delta)
{
    auto physics = PhysicsManager::get().get_physics_component(id);
    world_transform.position = physics->position;
    recalc_local_transform();
}

void Entity::face(Entity const& entity)
{
    float new_rotation = (entity.world_transform.position - world_transform.position).angle();
    world_transform.rotation = new_rotation;
    recalc_local_transform();
}

void Entity::face(vec2f_t const& vec)
{
    float new_rotation = (vec - world_transform.position).angle();
    world_transform.rotation = new_rotation;
    recalc_local_transform();
}

void Entity::set_local_transform(transform_t const& transform)
{
    local_transform = transform;
    recalc_world_transform();
}

void Entity::set_world_transform(transform_t const& transform)
{
    world_transform = transform;
    recalc_local_transform();
}

void Entity::recalc_local_transform() { local_transform = world_transform; }

void Entity::recalc_world_transform() { world_transform = local_transform; }
