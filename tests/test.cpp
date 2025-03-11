#include <iostream>
#include <cassert>

#include "Ray.h"
#include "Scalar.h"
#include "Sphere.h"
#include "Vector3.h"

using gfx::Ray;
using gfx::Scalar;
using gfx::Sphere;
using gfx::Vector3;

void Vector3OperatorsTest()
{
    Vector3 v(3, 4, 5);
    assert(v + Vector3(1, 1, 1) == Vector3(4, 5, 6));
    assert(v * 2 == Vector3(6, 8, 10));
    v *= -1;
    assert(v == Vector3(-3, -4, -5));

    const Vector3 w(-1, -30, -8);
    const Vector3 r = Cross(v, w);

    assert(gfx::IsZero(Dot(r, v)));
    assert(gfx::IsZero(Dot(r, w)));
}

void RaySphereIntersectionTest()
{
    const Sphere sphere(Vector3::origin, 5);
    const Ray ray(
        Vector3(10, 10, 10),
        Vector3(-1, -1, -1)
    );
    const Vector3 hit = ray.Intersect(sphere);
    const Scalar distance = Distance(hit, sphere.center);
    std::cout << std::format("Hit point = {}\nDistance from sphere = {}", hit, distance)
        << std::endl;

    assert(!(hit == Vector3::infinity));
    assert(gfx::AreEqual(distance, sphere.radius));
}

int main()
{
    Vector3OperatorsTest();
    RaySphereIntersectionTest();
    return 0;
}
