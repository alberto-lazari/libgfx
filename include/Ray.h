#pragma once

#include "Vector3.h"
#include "Sphere.h"

namespace gfx
{

class Ray
{
private:
    Vector3 _start;
    Vector3 _dir;

public:
    constexpr Ray()
        : _start(Vector3::origin())
        , _dir(Vector3::zero())
    {
    }

    constexpr Ray(const Vector3& start, const Vector3& dir)
        : _start(start)
        , _dir(dir.normalized())
    {
    }

    constexpr const Vector3& start() const { return _start; }
    constexpr Vector3& start() { return _start; }
    constexpr Ray& start(const Vector3& start)
    {
        _start = start.normalized();
        return *this;
    }

    constexpr const Vector3& dir() const { return _dir; }
    constexpr Vector3& dir() { return _dir; }
    constexpr Ray& dir(const Vector3& dir)
    {
        _dir = dir.normalized();
        return *this;
    }

    constexpr Vector3 intersect(const Sphere& s) const
    {
        const Vector3 G = _start;
        const Vector3 d = _dir;
        const Vector3 C = s.center;
        const Scalar r = s.radius;

        // Solve a k^2 + b k + c = 0
        const Scalar a = d.squared_norm();
        const Scalar b = dot(G - C, d);
        const Scalar c = (G - C).squared_norm() - r * r;

        const Scalar delta = b * b - a * c;
        if (delta < 0) return Vector3::infinity();

        const Scalar k = ( -b - std::sqrt(delta) ) / a;
        if (k < 0) return Vector3::infinity();

        return G + k * d;
    }
};

} // namespace gfx
