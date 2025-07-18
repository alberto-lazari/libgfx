#include "Ray.h"

namespace gfx
{

Ray::Ray()
    : _dir(Vector3())
    , start(Vector3::origin)
{
}

Ray::Ray(const Vector3& start, const Vector3& dir)
    : _dir(dir.normalized())
    , start(start)
{
}

Ray& Ray::set_dir(const Vector3& dir)
{
    _dir = dir.normalized();
    return *this;
}

const Vector3& Ray::dir() const
{
    return _dir;
}

Vector3& Ray::dir()
{
    return _dir;
}

Vector3 Ray::intersect(const Sphere& s) const
{
    const Vector3 G = start;
	const Vector3 d = _dir;
	const Vector3 C = s.center;
	const Scalar r = s.radius;

	// Solve a k^2 + b k + c = 0
	const Scalar a = d.squared_norm();
	const Scalar b = dot(G - C, d);
	const Scalar c = (G - C).squared_norm() - r * r;

	const Scalar delta = b * b - a * c;
	if (delta < 0) return Vector3::infinity;

	const Scalar k = ( -b - std::sqrt(delta) ) / a;
	if (k < 0) return Vector3::infinity;

	return G + k * d;
}

} // namespace gfx
