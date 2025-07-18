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

void test_vector3_operators()
{
    Vector3 z {};
    assert(z == Vector3::zero());

    Vector3 l { .x = -1 };
    assert(l == Vector3::left());

    Vector3 v { 3, 4, 5 };
    assert(v + Vector3::one() == Vector3(4, 5, 6));
    assert(v * 2 == Vector3(6, 8, 10));
    v *= -1;
    assert(v == Vector3(-3, -4, -5));

    const Vector3 w { -1, -30, -8 };
    const Vector3 r = cross(v, w);

    assert(gfx::is_zero(dot(r, v)));
    assert(gfx::is_zero(dot(r, w)));
}

void test_ray_sphere_intersection()
{
    const Sphere sphere { Vector3::origin(), 5 };
    const Ray ray {
        10 * Vector3::one(),
        -Vector3::one(),
    };
    const Vector3 hit = ray.intersect(sphere);
    const Scalar dist = distance(hit, sphere.center);
    std::cout << std::format("Hit point = {}\nDistance from sphere = {}", hit, dist)
        << std::endl;

    assert(hit != Vector3::infinity());
    assert(gfx::are_equal(dist, sphere.radius));
}

int main()
{
    test_vector3_operators();
    test_ray_sphere_intersection();

    return 0;
}
