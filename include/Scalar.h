#pragma once

#include <ostream>

namespace gfx
{

typedef float Scalar;

inline constexpr Scalar EPSILON = 1e-5f;

constexpr bool is_zero(Scalar k) { return std::abs(k) < EPSILON; }
constexpr bool are_equal(Scalar a, Scalar b) { return is_zero(a - b); }

template <typename T>
constexpr T lerp(const T& a, const T& b, Scalar alpha)
{
    return b * alpha + a * (1 - alpha);
}

} // namespace gfx
