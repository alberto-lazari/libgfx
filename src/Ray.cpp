#include "Ray.h"

namespace gfx
{

Ray::Ray() : dir(Vector3()), start(Vector3::origin) {}
Ray::Ray(const Vector3& start, const Vector3& dir)
    : dir(dir.Normalized()), start(start) {}

Ray& Ray::SetDir(const Vector3& dir)
{
    this->dir = dir.Normalized();
    return *this;
}

const Vector3& Ray::Dir() const
{
    return dir;
}

Vector3& Ray::Dir()
{
    return dir;
}

Vector3 Ray::Intersect(const Sphere& sphere) const
{
    const Vector3 G = start;
	const Vector3 d = dir;
	const Vector3 C = sphere.center;
	const Scalar r = sphere.radius;

	// Solve a k^2 + b k + c = 0
	const Scalar a = d.SquaredNorm();
	const Scalar b = Dot(G - C, d);
	const Scalar c = (G - C).SquaredNorm() - r * r;

	const Scalar delta = b * b - a * c;
	if (delta < 0) return Vector3::infinity;

	const Scalar k = ( -b - std::sqrt(delta) ) / a;
	if (k < 0) return Vector3::infinity;

	return G + k * d;
}

} // namespace gfx
