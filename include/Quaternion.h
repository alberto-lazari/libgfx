#pragma once

#include "Scalar.h"
#include "Vector3.h"

namespace gfx
{

struct Quaternion
{
    Vector3 imaginary;
    Scalar real;

    static constexpr Quaternion i() noexcept { return { .imaginary = { .x = 1 } }; }
    static constexpr Quaternion j() noexcept { return { .imaginary = { .y = 1 } }; }
    static constexpr Quaternion k() noexcept { return { .imaginary = { .z = 1 } }; }

    constexpr Scalar x() const noexcept { return imaginary.x; }
    constexpr Scalar y() const noexcept { return imaginary.y; }
    constexpr Scalar z() const noexcept { return imaginary.z; }
    constexpr Scalar w() const noexcept { return real; }

    constexpr Quaternion with_imaginary(const Vector3& new_imaginary) const noexcept
    {
        return { new_imaginary, real };
    }

    constexpr Quaternion with_real(const Scalar new_real) const noexcept
    {
        return { imaginary, new_real };
    }


    constexpr Quaternion operator*(const Scalar k) const noexcept
    {
        return { imaginary * k, real * k };
    }

    constexpr Quaternion operator-() const noexcept
    {
        return { -imaginary, -real };
    }

    constexpr Quaternion operator+(const Quaternion& q) const noexcept
    {
        return { imaginary + q.imaginary, real + q.real };
    }

    constexpr Quaternion operator-(const Quaternion& q) const noexcept
    {
        return { imaginary - q.imaginary, real - q.real };
    }

    constexpr Quaternion operator*(const Quaternion& q) const noexcept
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

    constexpr bool operator==(const Quaternion& q) const noexcept
    {
        return imaginary == q.imaginary
            && are_equal(real, q.real);
    }

    constexpr Quaternion& operator*=(const Scalar k) noexcept
    {
        imaginary *= k;
        real *= k;
        return *this;
    }


    constexpr Scalar dot(const Quaternion& q) const noexcept
    {
        return imaginary.dot(q.imaginary) + real * q.real;
    }

    constexpr Quaternion conjugated() const noexcept
    { 
        return with_imaginary(-imaginary);
    }

    constexpr Scalar squared_norm() const noexcept
    {
        return imaginary.squared_norm() + real * real;
    }

    constexpr Scalar norm() const noexcept
    {
        return std::sqrt(squared_norm());
    }

    constexpr Quaternion normalized() const noexcept
    {
        return *this * (1 / norm());
    }

    constexpr bool is_rotation() const noexcept
    {
        return are_equal(squared_norm(), 1);
    }

    constexpr Quaternion inverse() const noexcept
    {
        return conjugated() * (1 / squared_norm());
    }


    constexpr Quaternion& conjugate() noexcept
    {
        imaginary *= -1;
        return *this;
    }

    constexpr Quaternion& normalize() noexcept
    {
        return *this *= 1 / norm();
    }

    constexpr Quaternion& invert() noexcept
    {
        return conjugate() *= (1 / squared_norm());
    }
};

constexpr Scalar dot(const Quaternion& p, const Quaternion& q) noexcept
{
    return p.dot(q);
}

constexpr Scalar distance(const Quaternion& p, const Quaternion& q) noexcept
{
    return dot(p, q);
}

} // namespace gfx

// Scaling commutative closure (k q = q k)
constexpr gfx::Quaternion operator*(const gfx::Scalar k, const gfx::Quaternion& q) noexcept
{
    return q * k;
}
