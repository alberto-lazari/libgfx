#pragma once

#include <ostream>

namespace gfx
{

#define EPSILON 1e-5f

typedef float Scalar;

bool IsZero(Scalar k);
bool AreEqual(Scalar a, Scalar b);

} // namespace gfx
