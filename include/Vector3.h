#pragma once

#include "gfx.h"
#include "Scalar.h"

#include <cmath>
#include <format>
#include <ostream>

namespace gfx
{

struct Vector3;
constexpr bool are_equal(const Vector3& v, const Vector3& w, const Scalar ε) noexcept;

struct Vector3
{
    Scalar x;
    Scalar y;
    Scalar z;

    static constexpr Vector3 origin()    noexcept { return {}; }
    static constexpr Vector3 zero()      noexcept { return {}; }
    static constexpr Vector3 one()       noexcept { return { 1, 1, 1 }; }
    static constexpr Vector3 infinity()  noexcept { return { INFINITY, INFINITY, INFINITY }; }
    static constexpr Vector3 right()     noexcept { return { .x = +1 }; }
    static constexpr Vector3 left()      noexcept { return { .x = -1 }; }
    static constexpr Vector3 up()        noexcept { return { .y = +1 }; }
    static constexpr Vector3 down()      noexcept { return { .y = -1 }; }
    static constexpr Vector3 forwards()  noexcept { return { .z = +1 }; }
    static constexpr Vector3 backwards() noexcept { return { .z = -1 }; }

    /**
     * Subscript, math-like accessor.
     *
     * @param n Index of the elemtent.
     *          Just like in maths the first index is 1 (v_1, v_2, ...).
     * @return v_n, or NaN if index is out of bounds.
     */
    constexpr Scalar element(const unsigned n) const noexcept
    {
        switch (n)
        {
            case 1: return x;
            case 2: return y;
            case 3: return z;
            default: return NAN;
        }
    }

    constexpr Vector3 with_x(const Scalar other_x) const noexcept { return { other_x, y, z }; }
    constexpr Vector3 with_y(const Scalar other_y) const noexcept { return { x, other_y, z }; }
    constexpr Vector3 with_z(const Scalar other_z) const noexcept { return { x, y, other_z }; }

    constexpr Vector3 operator*(const Scalar k) const noexcept
    {
        return {
            x * k,
            y * k,
            z * k,
        };
    }

    constexpr Vector3 operator-() const noexcept
    {
        return { -x, -y, -z };
    }

    constexpr Vector3 operator+(const Vector3& v) const noexcept
    {
        return {
            x + v.x,
            y + v.y,
            z + v.z,
        };
    }

    constexpr Vector3 operator-(const Vector3& v) const noexcept
    {
        return {
            x - v.x,
            y - v.y,
            z - v.z,
        };
    }

    constexpr bool operator==(const Vector3& v) const noexcept
    {
        return are_equal(*this, v);
    }

    constexpr Vector3& operator*=(const Scalar k) noexcept
    {
        x *= k;
        y *= k;
        z *= k;
        return *this;
    }

    constexpr Vector3& operator+=(const Vector3& v) noexcept
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }


    constexpr Scalar dot(const Vector3& v) const noexcept
    {
        return x * v.x
            + y * v.y
            + z * v.z;
    }

    constexpr Vector3 cross(const Vector3& v) const noexcept
    {
        return {
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x,
        };
    }


    constexpr Scalar squared_norm() const noexcept
    {
        const Vector3 v = *this;
        return v.dot(v);
    }

    constexpr Scalar norm() const noexcept
    {
        return std::sqrt(squared_norm());
    }

    constexpr Vector3 normalized() const noexcept
    {
        return *this * (1 / norm());
    }

    constexpr Vector3& normalize() noexcept
    {
        return *this *= 1 / norm();
    }
};

constexpr bool are_equal(const Vector3& v, const Vector3& w, const Scalar ε) noexcept
{
    return are_equal(v.x, w.x, ε)
        && are_equal(v.y, w.y, ε)
        && are_equal(v.z, w.z, ε);
}

constexpr Scalar dot(const Vector3& v, const Vector3& w) noexcept
{
    return v.dot(w);
}

constexpr Vector3 cross(const Vector3& v, const Vector3& w) noexcept
{
    return v.cross(w);
}

constexpr Scalar distance(const Vector3& a, const Vector3& b) noexcept
{
    return (b - a).norm();
}

} // namespace gfx

// Scaling commutative closure (k v = v k)
constexpr gfx::Vector3 operator*(const gfx::Scalar k, const gfx::Vector3& v) noexcept
{
    return v * k;
}

GFX_API std::ostream& operator<<(std::ostream& os, const gfx::Vector3& v);


namespace std
{

template <>
struct formatter<gfx::Vector3>
{
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const gfx::Vector3& v, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "({}, {}, {})", v.x, v.y, v.z);
    }
};

} // namespace std
