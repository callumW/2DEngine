#include "Bullet.h"

Bullet::Bullet() : Entity("./assets/bullet.bmp", {0, 0, 5, 5}) {}


void Bullet::update(float delta)
{
    age += delta;

    if (age > BULLET_LIFE_SPAN) {
        // DIE!
        is_alive = false;
    }
    else {
        Entity::update(delta);
    }
}
