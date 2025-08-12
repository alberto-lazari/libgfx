#include <iostream>
#include <cassert>

#include "Matrix3.h"
#include "Quaternion.h"
#include "Ray.h"
#include "Rotation.h"
#include "Scalar.h"
#include "Sphere.h"
#include "Vector3.h"

using gfx::Matrix3;
using gfx::Quaternion;
using gfx::Ray;
using gfx::Rotation;
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

void test_180_y()
{
    const Vector3 p = { 2, 1, 5 };
    const Rotation y_180 = Rotation::from_axis_angle_degrees({ .y = 1 }, 180);

    const Vector3 p1 = y_180.rotate(p);

    // 180 deg rotation on Y axis keeps Y and inverts X and Z
    assert(p1 == p.with_x(-p.x).with_z(-p.z));

    // Inverse of rotation should get back to the original
    const Vector3 p_inv = y_180.inverse().rotate(p1);
    assert(p_inv == p);

    // Double 180 deg rotation should get back to the original
    const Vector3 p2 = y_180.rotate(p1);
    assert(p2 == p);

    // Test Euler angles too
    const Rotation y_180_euler = Rotation::from_euler_degrees({ .y = 180 });
    assert(y_180_euler.rotate(p) == p1);
}

void test_60_axis()
{
    const Vector3 â = Vector3 { 12, 3.2, -4.8 }.normalized();
    const Rotation â_60 = Rotation::from_axis_angle_degrees(â, 60);
    const Vector3 p = { 3, -1, 8 };

    Vector3 p1 = p;
    for (int i = 0; i < 6; ++i)
    {
        p1 = â_60.rotate(p1);
    }

    // 6 60 deg rotations should get back to the original
    assert(p1 == p);

    // Test optimized rotation against raw formula implementation
    assert(â_60.rotate(p) == â_60.naive_rotate(p));
}

void test_rot_matrix()
{
    const Rotation r = Rotation::from_euler_degrees({ 32, 124, -54 });
    const Vector3 p = { 5, 3, 12 };

    const Vector3 p1 = r.rotate(p);
    const Vector3 Mp = r.as_matrix3() * p;

    assert(p1 == Mp);

    // Test composition with another rotation
    const Rotation r2 = Rotation::from_axis_angle_degrees({ 0.5, -1, 0.25 }, 35);
    assert(r.then(r2).rotate(p) == r2.as_matrix3() * r.as_matrix3() * p);
}

int main()
{
    test_vector3_operators();
    test_ray_sphere_intersection();
    test_quaternion();
    test_180_y();
    test_60_axis();
    test_rot_matrix();

    return 0;
}
