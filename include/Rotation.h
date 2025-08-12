#pragma once

#include "Matrix3.h"
#include "Quaternion.h"
#include "Scalar.h"
#include "Vector3.h"

#include <cmath>

namespace gfx
{

class Rotation
{
private:
    Quaternion _q;

    constexpr Rotation(const Quaternion& q) noexcept
        : _q(q)
    {
    }

public:
    constexpr Rotation() noexcept
        // Null rotation (around the null axis)
        : _q { Vector3::zero(), 1 }
    {
    }

    static constexpr Rotation from_quaternion(const Quaternion& q) noexcept
    {
        return q.normalized();
    }

    static constexpr Rotation from_axis_angle(const Vector3& â, const Scalar α) noexcept
    {
        return {{ â.normalized() * std::sin(α / 2), std::cos(α / 2) }};
    }

    /**
     * Construct rotation from a triple (x, y, z) of eurler angles.
     * Follow Unity's roll, pitch, yaw order (z, x, y).
     */
    static constexpr Rotation from_euler(const Vector3& angles) noexcept
    {
        const Scalar α = angles.x;
        const Scalar β = angles.y;
        const Scalar γ = angles.z;

        const Rotation roll = from_axis_angle(Vector3::forwards(), γ);
        const Rotation pitch = from_axis_angle(Vector3::right(), α);
        const Rotation yaw = from_axis_angle(Vector3::up(), β);

        return roll.then(pitch).then(yaw);
    }


    constexpr const Quaternion& as_quaternion() const noexcept { return _q; }

    constexpr Matrix3 as_matrix3() const noexcept
    {
        const Scalar w = _q.w();
        const Scalar x = _q.x();
        const Scalar y = _q.y();
        const Scalar z = _q.z();

        const Scalar half = 0.5;

        // Of course I did not derive this myself, this is from:
        // https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation#Quaternion-derived_rotation_matrix
        return 2 * Matrix3 {
            {
                half - (y * y + z * z),
                x * y - z * w,
                x * z + y * w,
            },
            {
                x * y + z * w,
                half - (x * x + z * z),
                y * z + x * w,
            },
            {
                x * z + y * w,
                y * z + x * w,
                half - (x * x + y * y),
            },
        };
    }


    constexpr Rotation nlerp(const Rotation& rotation, const Scalar α) const noexcept
    {
        const Quaternion& p = _q;
        Quaternion q = rotation._q;

        // Take shortest path
        q = p.dot(q) < 0 ? -q : q;

        return lerp(p, q, α).normalized();
    }

    constexpr Rotation slerp(const Rotation& rotation, const Scalar α) const noexcept
    {
        const Quaternion& q1 = _q;
        Quaternion q2 = rotation._q;
        const Scalar u = α;

        // Take shortest path
        const Scalar dot = q1.dot(q2);
        q2 = dot < 0 ? -q2 : q2;

        // Use nlerp if rotations are too close, to minimize error
        if (is_zero(dot)) return lerp(q1, q2, u).normalized();

        // q1 dot q2 = cos θ, since q1 and q2 are rotations, having norm = 1
        const Scalar θ = std::acos(dot);

        // Two distinct ways to compute Slerp, according to:
        // Ken Shoemake, 1985, Animating Rotation with Quaternion Curves, Section 3.3
        // https://doi.org/10.1145/325165.325242
        //
        //     +------------------------------------+
        // (1) | Slerp(q1, q2; u) = q1 (q1^-1 q2)^u |
        //     +------------------------------------+
        //
        //     +--------------------------------------------------+
        //     |                    sin (1 - u) θ      sin u θ    |
        // (2) | Slerp(q1, q2; u) = ------------- q1 + ------- q2 |
        //     |                        sin θ           sin θ     |
        //     +--------------------------------------------------+
        //
        // I choose option (2) to avoid defining the power of a quaternion.
        const Scalar sin_θ = std::sin(θ);

        return std::sin((1 - u) * θ) / sin_θ * q1
             + std::sin(u * θ)       / sin_θ * q2;
    }

    /**
     * Combine with rotation, applying the current rotation first.
     */
    constexpr Rotation then(const Rotation& rotation) const noexcept
    {
        return rotation._q * _q;
    }

    /**
     * Naïve approach, using the raw formula and full quaternion products.
     */
    constexpr Vector3 naive_rotate(const Vector3& v) const noexcept
    {
        const Quaternion p = { v, 0 };
        const Quaternion p1 = _q * p * _q.conjugated();
        return p1.imaginary;
    }

    /**
     * Optimized approach, obtained from quaternion product simplification.
     */
    constexpr Vector3 rotate(const Vector3& v) const noexcept
    {
        const Vector3 w = _q.imaginary;
        const Scalar a = _q.real;
        return a * a * v + 2 * a * w.cross(v) + w.dot(v) * w - w.cross(v).cross(w);
    }

    constexpr Rotation inverse() const noexcept
    {
        return _q.conjugated();
    }


    constexpr Rotation& invert() noexcept
    {
        _q.conjugate();
        return *this;
    }
};

constexpr bool are_equivalent(const Rotation& a, const Rotation& b, const Scalar ε) noexcept
{
    const Quaternion& qa = a.as_quaternion();
    const Quaternion& qb = b.as_quaternion();
    return are_equal(qa, qb, ε) || are_equal(qa, -qb, ε);
}

constexpr bool are_equivalent(const Rotation& a, const Rotation& b) noexcept
{
    return are_equivalent(a, b, EPSILON);
}

constexpr Rotation nlerp(const Rotation& a, const Rotation& b, const Scalar α) noexcept
{
    return a.nlerp(b, α);
}

constexpr Rotation slerp(const Rotation& a, const Rotation& b, const Scalar α) noexcept
{
    return a.slerp(b, α);
}

} // namespace gfx
