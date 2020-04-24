#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

float const PLAYER_MOVEMENT_SPEED = 250.0f; // pixels per second

class Player : public Entity {
public:
    Player();

    virtual void update(float delta);
};
#endif
