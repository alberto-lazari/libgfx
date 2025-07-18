#pragma once

#include "gfx.h"

#include "Scalar.h"

#include <ostream>
#include <format>

namespace gfx
{

struct GFX_API Vector3
{
    Scalar x;
    Scalar y;
    Scalar z;

    static const Vector3 origin;
    static const Vector3 zero;
    static const Vector3 infinity;
    static const Vector3 right;
    static const Vector3 left;
    static const Vector3 up;
    static const Vector3 down;
    static const Vector3 forwards;
    static const Vector3 backwards;

    Vector3 operator*(Scalar k) const;
    Vector3 operator+(const Vector3& v) const;
    Vector3 operator-(const Vector3& v) const;
    Vector3 operator-() const;

    Scalar squared_norm() const;
    Scalar norm() const;
    Vector3 normalized() const;
    Vector3& normalize();

    bool operator==(const Vector3& v) const;

    Vector3& operator*=(Scalar k);
    Vector3& operator+=(const Vector3& v);
};

GFX_API Scalar dot(const Vector3& v, const Vector3& w);
GFX_API Vector3 cross(const Vector3& v, const Vector3& w);
GFX_API Scalar distance(const Vector3& a, const Vector3& b);

} // namespace gfx

// Scaling commutative closure (k v = v k)
GFX_API gfx::Vector3 operator*(gfx::Scalar k, const gfx::Vector3& v);

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
