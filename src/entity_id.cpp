#include "entity_id.h"

std::ostream& operator<<(std::ostream& stream, entity_id_t const& e)
{
    stream << "id(" << e.index() << "|" << e.generation() << ")";
    return stream;
}

bool operator==(entity_id_t const& lhs, entity_id_t const& rhs) { return lhs.idx == rhs.idx; }
