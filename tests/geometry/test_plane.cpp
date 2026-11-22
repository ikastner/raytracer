#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "geometry/plane.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("Ray hits horizontal plane", "[plane]") {
    const Plane floor(Vector(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0));
    const Ray ray(Vector(1.0, 2.0, -3.0), Vector(0.0, -1.0, 0.0));

    const auto hit = floor.isHitBy(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(3.0, 1e-6));
    requireVectorsEqual(hit->point, Vector(1.0, -1.0, -3.0));
    requireVectorsEqual(hit->normal, Vector(0.0, 1.0, 0.0));
}

TEST_CASE("Parallel ray misses plane", "[plane]") {
    const Plane floor(Vector(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0));
    const Ray ray(Vector(1.0, 2.0, -3.0), Vector(1.0, 0.0, 0.0));

    REQUIRE_FALSE(floor.isHitBy(ray).has_value());
}

TEST_CASE("Ray pointing away from plane misses", "[plane]") {
    const Plane floor(Vector(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0));
    const Ray ray(Vector(1.0, 2.0, -3.0), Vector(0.0, 1.0, 0.0));

    REQUIRE_FALSE(floor.isHitBy(ray).has_value());
}

TEST_CASE("Ray hitting plane from underneath flips normal toward ray", "[plane]") {
    const Plane floor(Vector(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0));
    const Ray ray(Vector(1.0, -4.0, -3.0), Vector(0.0, 1.0, 0.0));

    const auto hit = floor.isHitBy(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(3.0, 1e-6));
    requireVectorsEqual(hit->point, Vector(1.0, -1.0, -3.0));
    requireVectorsEqual(hit->normal, Vector(0.0, -1.0, 0.0));
}
