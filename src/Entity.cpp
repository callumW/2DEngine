#include "Entity.h"

std::ostream& operator<<(std::ostream& stream, entity_t const& e)
{
    stream << e.uuid;
    return stream;
}

bool operator==(entity_t const& lhs, entity_t const& rhs) { return lhs.uuid == rhs.uuid; }
