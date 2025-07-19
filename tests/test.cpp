#include <iostream>
#include <cassert>

#include "Quaternion.h"
#include "Ray.h"
#include "Scalar.h"
#include "Sphere.h"
#include "Vector3.h"

using gfx::Quaternion;
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

    assert(gfx::lerp(z, v, 0) == z);
    assert(gfx::lerp(z, v, 1) == v);
    assert(gfx::lerp(z, v, 0.5) == 0.5 * v);
    assert(gfx::lerp(-v, v, 0.5) == Vector3::zero());
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

    assert(hit != Vector3::infinity());
    assert(gfx::are_equal(dist, sphere.radius));
}

void test_quaternion()
{
    const Quaternion zero {};
    assert(!zero.is_rotation());

    const Quaternion i = Quaternion::i();
    const Quaternion j = Quaternion::j();
    const Quaternion k = Quaternion::k();

    assert(i.is_rotation());
    assert(j.is_rotation());
    assert(k.is_rotation());

    assert(i * j == k);
    assert(j * k == i);
    assert(k * i == j);
    assert(j * i == -k);
    assert(k * j == -i);
    assert(i * k == -j);
    assert(i * k == -j);

    const Quaternion q { { 3, 2, -5 }, -2 };
    assert(q.conjugated() == q.with_imaginary(-q.imaginary));
    assert(q.conjugated() == -q.with_real(-q.real));
    assert(!q.is_rotation());
    assert(q.normalized().is_rotation());
}

int main()
{
    test_vector3_operators();
    test_ray_sphere_intersection();
    test_quaternion();

    return 0;
}
