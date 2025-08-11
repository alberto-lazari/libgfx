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

public:
    constexpr Rotation()
        // Null rotation (around the null axis)
        : _q { Vector3::zero(), 1 }
    {
    }

    constexpr Rotation(const Quaternion& q)
        : _q(q.normalized())
    {
    }


    /**
     * Combine with rotation, applying the current rotation first.
     */
    constexpr Rotation then(const Rotation& rotation) const
    {
        return rotation.as_quaternion() * as_quaternion();
    }


    static constexpr Rotation from_axis_angle(const Vector3& axis, const Scalar angle)
    {
        return Rotation({ axis * std::sin(angle / 2), std::cos(angle / 2) });
    }

    /**
     * Construct rotation from a triple (x, y, z) of eurler angles.
     * Follow Unity's roll, pitch, yaw order (z, x, y).
     */
    static constexpr Rotation from_euler(const Vector3& angles)
    {
        const Scalar alpha = angles.x;
        const Scalar beta = angles.y;
        const Scalar gamma = angles.z;

        const Rotation roll = from_axis_angle(Vector3::forwards(), gamma);
        const Rotation pitch = from_axis_angle(Vector3::right(), alpha);
        const Rotation yaw = from_axis_angle(Vector3::up(), beta);

        return roll.then(pitch).then(yaw);
    }


    constexpr const Quaternion& as_quaternion() const
    {
        return _q;
    }

    constexpr Matrix3 as_matrix3() const
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
};

} // namespace gfx
