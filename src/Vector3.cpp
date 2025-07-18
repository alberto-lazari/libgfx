#include "Vector3.h"

#include <cmath>

namespace gfx
{

GFX_API const Vector3 Vector3::origin    = {};
GFX_API const Vector3 Vector3::infinity  = { INFINITY, INFINITY, INFINITY };
GFX_API const Vector3 Vector3::right     = { +1, 0, 0 };
GFX_API const Vector3 Vector3::left      = { -1, 0, 0 };
GFX_API const Vector3 Vector3::up        = { 0, +1, 0 };
GFX_API const Vector3 Vector3::down      = { 0, -1, 0 };
GFX_API const Vector3 Vector3::forwards  = { 0, 0, +1 };
GFX_API const Vector3 Vector3::backwards = { 0, 0, -1 };

Vector3 Vector3::operator*(Scalar k) const
{
    return Vector3(
        x * k,
        y * k,
        z * k
    );
}

Vector3 Vector3::operator+(const Vector3& v) const
{
    return Vector3(
        x + v.x,
        y + v.y,
        z + v.z
    );
}

Vector3 Vector3::operator-(const Vector3& v) const
{
    return Vector3(
        x - v.x,
        y - v.y,
        z - v.z
    );
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

Scalar Vector3::squared_norm() const
{
    return dot(*this, *this);
}

Scalar Vector3::norm() const
{
    return std::sqrt(squared_norm());
}

Vector3 Vector3::normalized() const
{
    return *this * (1 / norm());
}

Vector3& Vector3::normalize()
{
    return *this *= 1 / norm();
}

bool Vector3::operator==(const Vector3& v) const
{
    return x == v.x
        && y == v.y
        && z == v.z;
}

Vector3& Vector3::operator*=(Scalar k)
{
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

Vector3& Vector3::operator+=(const Vector3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}


Scalar dot(const Vector3& v, const Vector3& w)
{
    return v.x * w.x
        + v.y * w.y
        + v.z * w.z;
}

Vector3 cross(const Vector3& v, const Vector3& w)
{
    return Vector3(
        v.y * w.z - v.z * w.y,
        v.z * w.x - v.x * w.z,
        v.x * w.y - v.y * w.x
    );
}

Scalar distance(const Vector3& a, const Vector3& b)
{
    return (b - a).norm();
}

} // namespace gfx

gfx::Vector3 operator*(gfx::Scalar k, const gfx::Vector3& v)
{
    return v * k;
}

std::ostream& operator<<(std::ostream& os, const gfx::Vector3& v)
{
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}
