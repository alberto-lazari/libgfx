#pragma once

#include <cmath>

namespace gfx
{

typedef float Scalar;

inline constexpr const Scalar EPSILON = 1e-5f;

constexpr bool is_zero(const Scalar k) noexcept { return std::abs(k) < EPSILON; }
constexpr bool are_equal(const Scalar a, const Scalar b) noexcept { return is_zero(a - b); }

template <typename T>
constexpr T lerp(const T& a, const T& b, const Scalar alpha) noexcept
{
    return b * alpha + a * (1 - alpha);
}

} // namespace gfx
