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
        : _q(q.normalized())
    {
    }

public:
    constexpr Rotation() noexcept
        // Null rotation (around the null axis)
        : _q { Vector3::zero(), 1 }
    {
    }

    static constexpr Rotation from_quaternion(const Quaternion& q) noexcept { return { q }; }

    static constexpr Rotation from_axis_angle(const Vector3& axis, const Scalar angle) noexcept
    {
        return {{ axis * std::sin(angle / 2), std::cos(angle / 2) }};
    }

    /**
     * Construct rotation from a triple (x, y, z) of eurler angles.
     * Follow Unity's roll, pitch, yaw order (z, x, y).
     */
    static constexpr Rotation from_euler(const Vector3& angles) noexcept
    {
        const Scalar alpha = angles.x;
        const Scalar beta = angles.y;
        const Scalar gamma = angles.z;

        const Rotation roll = from_axis_angle(Vector3::forwards(), gamma);
        const Rotation pitch = from_axis_angle(Vector3::right(), alpha);
        const Rotation yaw = from_axis_angle(Vector3::up(), beta);

        return roll.then(pitch).then(yaw);
    }


    constexpr const Quaternion& as_quaternion() const noexcept { return _q; }

    constexpr Matrix3 as_matrix3() const noexcept
    {
        const Scalar w = _q.w();
        const Scalar x = _q.x();
        const Scalar y = _q.y();
        const Scalar z = _q.z();

        // Of course I did not derive this myself, this is from:
        // https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation#Quaternion-derived_rotation_matrix
        return 2 * Matrix3 {
            {
                0.5f - (y * y + z * z),
                x * y - z * w,
                x * z + y * w,
            },
            {
                x * y + z * w,
                0.5f - (x * x + z * z),
                y * z + x * w,
            },
            {
                x * z + y * w,
                y * z + x * w,
                0.5f - (x * x + y * y),
            },
        };
    }

    /**
     * Combine with rotation, applying the current rotation first.
     */
    constexpr Rotation then(const Rotation& rotation) const noexcept
    {
        return rotation.as_quaternion() * as_quaternion();
    }

    /**
     * Naive approach, using the raw formula and full quaternion products.
     */
    constexpr Vector3 naive_rotate(const Vector3& v) const noexcept
    {
        const Quaternion q = as_quaternion();
        const Quaternion p = { v, 0 };
        const Quaternion p1 = q * p * q.conjugated();
        return p1.imaginary;
    }

    /**
     * Optimized approach, obtained from quaternion product simplification.
     */
    constexpr Vector3 rotate(const Vector3& v) const noexcept
    {
        const Vector3 w = as_quaternion().imaginary;
        const Scalar a = as_quaternion().real;
        return a * a * v + 2 * a * w.cross(v) + w.dot(v) * w - w.cross(v).cross(w);
    }
};

} // namespace gfx
