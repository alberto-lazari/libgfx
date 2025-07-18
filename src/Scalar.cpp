#include "Scalar.h"

namespace gfx
{

bool is_zero(Scalar k)
{
    return std::abs(k) < EPSILON;
}

bool are_equal(Scalar a, Scalar b)
{
    return is_zero(a - b);
}

} // namespace gfx
