#include "ContactListener.h"
#include "Game.h"

#include <iostream>

void ContactListener::BeginContact(b2Contact* contact)
{
    if (contact->GetFixtureA()->GetFilterData().categoryBits & (1 << 4) ||
        contact->GetFixtureB()->GetFilterData().categoryBits & (1 << 4)) {
        std::cout << "Player collides!" << std::endl;

        Game* game = nullptr;
        if (contact->GetFixtureA()->GetFilterData().categoryBits & (1 << 4)) {
            game = static_cast<Game*>(contact->GetFixtureA()->GetUserData());
        }
        else {
            game = static_cast<Game*>(contact->GetFixtureB()->GetUserData());
        }

        if (game != nullptr) {
            // TODO verify that player landed from above?
            game->set_player_landed();
        }
    }
}
