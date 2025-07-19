#pragma once

#include "gfx.h"

#include "Vector3.h"
#include "Scalar.h"

namespace gfx
{

struct GFX_API Quaternion
{
    Vector3 imaginary;
    Scalar real;

    static constexpr Quaternion i() { return { .imaginary = { .x = 1 } }; }
    static constexpr Quaternion j() { return { .imaginary = { .y = 1 } }; }
    static constexpr Quaternion k() { return { .imaginary = { .z = 1 } }; }

    constexpr Quaternion with_imaginary(Vector3 new_imaginary) const
    {
        return { new_imaginary, real };
    }

    constexpr Quaternion with_real(Scalar new_real) const
    {
        return { imaginary, new_real };
    }


    constexpr Quaternion operator*(Scalar k) const
    {
        return { imaginary * k, real * k };
    }

    constexpr Quaternion operator-() const
    {
        return { -imaginary, -real };
    }

    constexpr Quaternion operator+(const Quaternion& q) const
    {
        return { imaginary + q.imaginary, real + q.real };
    }

    constexpr Quaternion operator-(const Quaternion& q) const
    {
        return { imaginary - q.imaginary, real - q.real };
    }

    constexpr Quaternion operator*(const Quaternion& q) const
    {
        const Vector3 v = imaginary;
        const Scalar  d = real;

        const Vector3 w = q.imaginary;
        const Scalar  h = q.real;

        return {
            v * h + w * d + v.cross(w),
            d * h - v.dot(w)
        };
    }

    constexpr bool operator==(const Quaternion& q) const
    {
        return imaginary == q.imaginary
            && are_equal(real, q.real);
    }

    constexpr Quaternion& operator*=(Scalar k)
    {
        imaginary *= k;
        real *= k;
        return *this;
    }


    constexpr Scalar dot(const Quaternion& q) const
    {
        return imaginary.dot(q.imaginary) + real * q.real;
    }

    constexpr Quaternion conjugated() const
    { 
        return with_imaginary(-imaginary);
    }

    constexpr Scalar squared_norm() const
    {
        return imaginary.squared_norm() + real * real;
    }

    constexpr Scalar norm() const
    {
        return std::sqrt(squared_norm());
    }

    constexpr Quaternion normalized() const
    {
        return *this * (1 / norm());
    }

    constexpr bool is_rotation() const
    {
        return are_equal(squared_norm(), 1);
    }

    constexpr Quaternion inverse() const
    {
        return conjugated() * (1 / squared_norm());
    }


    constexpr Quaternion& conjugate()
    {
        imaginary *= -1;
        return *this;
    }

    constexpr Quaternion& normalize()
    {
        return *this *= 1 / norm();
    }

    constexpr Quaternion& invert()
    {
        return conjugate() *= (1 / squared_norm());
    }
};

constexpr Scalar dot(const Quaternion& p, const Quaternion& q)
{
    return p.dot(q);
}

constexpr Scalar distance(const Quaternion& p, const Quaternion& q)
{
    return dot(p, q);
}

} // namespace gfx

// Scaling commutative closure (k q = q k)
constexpr gfx::Quaternion operator*(gfx::Scalar k, const gfx::Quaternion& q)
{
    return q * k;
}
