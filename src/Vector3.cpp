#include "Vector3.h"

std::ostream& operator<<(std::ostream& os, const gfx::Vector3& v)
{
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}
