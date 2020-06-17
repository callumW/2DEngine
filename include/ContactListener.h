#ifndef PHYSICS_COLLISION_CONTACT_H
#define PHYSICS_COLLISION_CONTACT_H

#include <box2d/box2d.h>

class ContactListener : public b2ContactListener {
public:
    virtual void BeginContact(b2Contact* contact) override;
};
#endif
