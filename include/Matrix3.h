#pragma once

#include "Scalar.h"
#include "Vector3.h"

namespace gfx
{

class Matrix3
{
private:
    Vector3 _rows[3];

public:
    constexpr Matrix3() noexcept
        : _rows {}
    {
    }

    constexpr Matrix3(
        const Vector3& row1,
        const Vector3& row2,
        const Vector3& row3) noexcept
        : _rows { row1, row2, row3 }
    {
    }

    constexpr Vector3 row(const unsigned n) const noexcept
    {
        if (n == 0 || n > 3) return { NAN, NAN, NAN };

        return _rows[n - 1];
    }

    constexpr Vector3 col(const unsigned n) const noexcept
    {
        if (n == 0 || n > 3) return { NAN, NAN, NAN };

        return {
            row(1).element(n),
            row(2).element(n),
            row(3).element(n),
        };
    }

    constexpr Scalar element(const unsigned r, const unsigned c) const noexcept
    {
        return row(r).element(c);
    }

    constexpr Matrix3 operator*(const Scalar k) const noexcept
    {
        return {
            k * row(1),
            k * row(2),
            k * row(3),
        };
    }

    constexpr Matrix3 operator*(const Matrix3& M) const noexcept
    {
        return {
            { row(1).dot(M.col(1)), row(1).dot(M.col(2)), row(1).dot(M.col(3)) },
            { row(2).dot(M.col(1)), row(2).dot(M.col(2)), row(2).dot(M.col(3)) },
            { row(3).dot(M.col(1)), row(3).dot(M.col(2)), row(3).dot(M.col(3)) },
        };
    }

    constexpr Vector3 operator*(const Vector3& v) const noexcept
    {
        return {
            row(1).dot(v),
            row(2).dot(v),
            row(3).dot(v),
        };
    }
};

} // namespace gfx

constexpr gfx::Matrix3 operator*(const gfx::Scalar k, const gfx::Matrix3& M) noexcept
{
    return M * k;
}
