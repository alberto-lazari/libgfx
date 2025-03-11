#include "Vector3.h"

#include <cmath>

namespace gfx
{

const Vector3 Vector3::origin     = Vector3();
const Vector3 Vector3::infinity   = Vector3(NAN, NAN, NAN);
const Vector3 Vector3::right      = Vector3(+1, 0, 0);
const Vector3 Vector3::left       = Vector3(-1, 0, 0);
const Vector3 Vector3::up         = Vector3(0, +1, 0);
const Vector3 Vector3::down       = Vector3(0, -1, 0);
const Vector3 Vector3::forwards   = Vector3(0, 0, +1);
const Vector3 Vector3::backwards  = Vector3(0, 0, -1);

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

Scalar Vector3::SquaredNorm() const
{
    return Dot(*this, *this);
}

Scalar Vector3::Norm() const
{
    return std::sqrt(SquaredNorm());
}

Vector3 Vector3::Normalized() const
{
    return *this * (1 / Norm());
}

Vector3& Vector3::Normalize()
{
    return *this *= 1 / Norm();
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


Scalar Dot(const Vector3& v, const Vector3& w)
{
    return v.x * w.x
        + v.y * w.y
        + v.z * w.z;
}

Vector3 Cross(const Vector3& v, const Vector3& w)
{
    return Vector3(
        v.y * w.z - v.z * w.y,
        v.z * w.x - v.x * w.z,
        v.x * w.y - v.y * w.x
    );
}

Scalar Distance(const Vector3& A, const Vector3& B)
{
    return (B - A).Norm();
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
