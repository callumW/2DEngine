#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H
#include <array>
#include <unordered_map>
#include <vector>

#include "ComponentManager.h"
#include "Entity.h"
#include "PhysicsComponent.h"

class PhysicsManager : public ComponentManager<physics_component_t> {
public:
    static PhysicsManager& get();

    void simulate(float delta);

    b2Body* create_body(b2BodyDef const& body_def) { return world.CreateBody(&body_def); }

    b2World& World() { return world; }

private:
    PhysicsManager() : world(GRAVITY){};

    virtual void pre_remove(physics_component_t* component) override;

    b2Vec2 const GRAVITY = {0.0f, -10.0f};
    b2World world;
};
#endif
