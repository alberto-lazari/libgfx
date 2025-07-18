#pragma once

#include "gfx.h"

#include "Vector3.h"

namespace gfx
{

struct GFX_API Sphere
{
    Vector3 center;
    Scalar radius;

    Sphere();
    Sphere(const Vector3& center, Scalar radius);
};

} // namespace gfx
