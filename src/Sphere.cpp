#include "Sphere.h"

namespace gfx
{

Sphere::Sphere() : center(Vector3::origin), radius(0) {}
Sphere::Sphere(const Vector3& _center, Scalar _radius)
    : center(_center), radius(_radius) {}

} // namespace gfx
