#pragma once

#include "gfx.h"

#include <ostream>

namespace gfx
{

typedef float Scalar;

inline constexpr Scalar EPSILON = 1e-5f;

GFX_API bool is_zero(Scalar k);
GFX_API bool are_equal(Scalar a, Scalar b);

} // namespace gfx
