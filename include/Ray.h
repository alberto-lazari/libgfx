#pragma once

#include "gfx.h"

#include "Vector3.h"
#include "Sphere.h"

namespace gfx
{

class GFX_API Ray
{
private:
    Vector3 _dir;

public:
    Vector3 start;

    Ray();
    Ray(const Vector3& start, const Vector3& dir);

    Ray& set_dir(const Vector3& dir);

    const Vector3& dir() const;
    Vector3& dir();

    Vector3 intersect(const Sphere& s) const;
};

} // namespace gfx
