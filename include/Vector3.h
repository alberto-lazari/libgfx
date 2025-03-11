#pragma once

#include "Scalar.h"

#include <ostream>

namespace gfx
{

class Vector3
{
public:
    Scalar x;
    Scalar y;
    Scalar z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(Scalar x, Scalar y, Scalar z) : x(x), y(y), z(z) {}

    // Edge cases
    static const Vector3 origin;
    static const Vector3 infinity;
    // Axes
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

    Scalar SquaredNorm() const;
    Scalar Norm() const;
    Vector3 Normalized() const;
    Vector3& Normalize();

    bool operator==(const Vector3& v) const;

    Vector3& operator*=(Scalar k);
    Vector3& operator+=(const Vector3& v);
};

Scalar Dot(const Vector3& v, const Vector3& w);
Vector3 Cross(const Vector3& v, const Vector3& w);
Scalar Distance(const Vector3& A, const Vector3& B);

} // namespace gfx

// Scaling commutative closure (k v = v k)
gfx::Vector3 operator*(gfx::Scalar k, const gfx::Vector3& v);

std::ostream& operator<<(std::ostream& os, const gfx::Vector3& v);

template <>
struct std::formatter<gfx::Vector3>
{
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const gfx::Vector3& v, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "({}, {}, {})", v.x, v.y, v.z);
    }
};
