#include "Scalar.h"

namespace gfx
{

bool IsZero(Scalar k)
{
    return std::abs(k) < EPSILON;
}

bool AreEqual(Scalar a, Scalar b)
{
    return IsZero(a - b);
}

} // namespace gfx
