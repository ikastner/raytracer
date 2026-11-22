#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "geometry/sphere.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("Ray hits off-centre sphere", "[sphere]") {
    const Sphere sphere(Vector(1.0, 2.0, -5.0), 2.0);
    const Ray ray(Vector(1.0, 2.0, 0.0), Vector(0.0, 0.0, -1.0));

    const auto hit = sphere.isHitBy(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(3.0, 1e-6));
    requireVectorsEqual(hit->point, Vector(1.0, 2.0, -3.0));
    requireVectorsEqual(hit->normal, Vector(0.0, 0.0, 1.0));
}

TEST_CASE("Ray misses sphere", "[sphere]") {
    const Sphere sphere(Vector(1.0, 2.0, -5.0), 2.0);
    const Ray ray(Vector(1.0, 5.0, 0.0), Vector(0.0, 0.0, -1.0));

    const auto hit = sphere.isHitBy(ray);

    REQUIRE_FALSE(hit.has_value());
}

TEST_CASE("Ray hits back side of sphere", "[sphere]") {
    const Sphere sphere(Vector(1.0, 2.0, -5.0), 2.0);
    const Ray ray(Vector(1.0, 2.0, 0.0), Vector(0.0, 0.0, 1.0));

    const auto hit = sphere.isHitBy(ray);

    REQUIRE_FALSE(hit.has_value());
}
