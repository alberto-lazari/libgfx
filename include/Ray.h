#pragma once

#include "Vector3.h"
#include "Sphere.h"

namespace gfx
{

class Ray
{
private:
    Vector3 dir;

public:
    Vector3 start;

    Ray();
    Ray(const Vector3& start, const Vector3& dir);

    Ray& SetDir(const Vector3& dir);

    const Vector3& Dir() const;
    Vector3& Dir();

    Vector3 Intersect(const Sphere& sphere) const;
};

} // namespace gfx
