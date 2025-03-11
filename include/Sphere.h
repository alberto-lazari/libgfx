#pragma once

#include "Vector3.h"

namespace gfx
{

class Sphere
{
public:
    Vector3 center;
    Scalar radius;

    Sphere();
    Sphere(const Vector3& center, Scalar radius);
};

} // namespace gfx
