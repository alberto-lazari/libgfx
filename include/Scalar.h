#pragma once

#include <cmath>

namespace gfx
{

typedef float Scalar;

constexpr bool is_zero(const Scalar k, const Scalar ε) noexcept { return std::abs(k) < ε; }
constexpr bool are_equal(const Scalar a, const Scalar b, const Scalar ε) noexcept
{
    return is_zero(a - b, ε);
}

inline constexpr const Scalar EPSILON = 1e-5f;

constexpr bool is_zero(const Scalar k) noexcept { return std::abs(k) < EPSILON; }

template <typename T>
constexpr bool are_equal(const T& a, const T& b) noexcept { return are_equal(a, b, EPSILON); }


template <typename T>
constexpr T lerp(const T& a, const T& b, const Scalar α) noexcept
{
    return b * α + a * (1 - α);
}

} // namespace gfx
