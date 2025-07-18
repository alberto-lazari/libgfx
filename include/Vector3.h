#pragma once

#include "gfx.h"

#include "Scalar.h"

#include <ostream>
#include <format>
#include <cmath>

namespace gfx
{

struct Vector3;

constexpr Scalar dot(const Vector3& v, const Vector3& w);
constexpr Vector3 cross(const Vector3& v, const Vector3& w);
constexpr Scalar distance(const Vector3& a, const Vector3& b);

struct Vector3
{
    Scalar x;
    Scalar y;
    Scalar z;

    static constexpr Vector3 origin()    { return {}; }
    static constexpr Vector3 zero()      { return {}; }
    static constexpr Vector3 one()       { return { 1, 1, 1 }; }
    static constexpr Vector3 infinity()  { return { INFINITY, INFINITY, INFINITY }; }
    static constexpr Vector3 right()     { return { .x = +1 }; }
    static constexpr Vector3 left()      { return { .x = -1 }; }
    static constexpr Vector3 up()        { return { .y = +1 }; }
    static constexpr Vector3 down()      { return { .y = -1 }; }
    static constexpr Vector3 forwards()  { return { .z = +1 }; }
    static constexpr Vector3 backwards() { return { .z = -1 }; }

    constexpr Vector3 operator*(Scalar k) const
    {
        return {
            x * k,
            y * k,
            z * k,
        };
    }

    constexpr Vector3 operator+(const Vector3& v) const
    {
        return {
            x + v.x,
            y + v.y,
            z + v.z,
        };
    }

    constexpr Vector3 operator-() const
    {
        return { -x, -y, -z };
    }

    constexpr Vector3 operator-(const Vector3& v) const
    {
        return *this + -v;
    }

    constexpr bool operator==(const Vector3& v) const
    {
        return x == v.x
            && y == v.y
            && z == v.z;
    }

    constexpr Vector3& operator*=(Scalar k)
    {
        x *= k;
        y *= k;
        z *= k;
        return *this;
    }

    constexpr Vector3& operator+=(const Vector3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }


    constexpr Scalar squared_norm() const
    {
        return dot(*this, *this);
    }

    constexpr Scalar norm() const
    {
        return std::sqrt(squared_norm());
    }

    constexpr Vector3 normalized() const
    {
        return *this * (1 / norm());
    }

    constexpr Vector3& normalize()
    {
        return *this *= 1 / norm();
    }


    constexpr Vector3 with_x(Scalar x)
    {
        return { x, this->y, this->z };
    }

    constexpr Vector3 with_y(Scalar y)
    {
        return { this->x, y, this->z };
    }

    constexpr Vector3 with_z(Scalar z)
    {
        return { this->x, this->y, z };
    }
};

constexpr Scalar dot(const Vector3& v, const Vector3& w)
{
    return v.x * w.x
        + v.y * w.y
        + v.z * w.z;
}

constexpr Vector3 cross(const Vector3& v, const Vector3& w)
{
    return {
        v.y * w.z - v.z * w.y,
        v.z * w.x - v.x * w.z,
        v.x * w.y - v.y * w.x,
    };
}

constexpr Scalar distance(const Vector3& a, const Vector3& b)
{
    return (b - a).norm();
}

} // namespace gfx

// Scaling commutative closure (k v = v k)
constexpr gfx::Vector3 operator*(gfx::Scalar k, const gfx::Vector3& v)
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
