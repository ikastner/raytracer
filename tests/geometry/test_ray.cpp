#include <catch2/catch_test_macros.hpp>

#include "geometry/ray.h"
#include "test_helpers.h"

TEST_CASE("Ray stores origin and direction", "[ray]") {
    const Vector origin(1.0, 2.0, 3.0);
    const Vector direction(4.0, -1.0, 2.0);
    const Ray ray(origin, direction);

    requireVectorsEqual(ray.origin(), Vector(1.0, 2.0, 3.0));
    requireVectorsEqual(ray.direction(), Vector(4.0, -1.0, 2.0));
}

TEST_CASE("Ray::at computes origin + t * direction", "[ray]") {
    const Ray ray(Vector(1.0, 2.0, 3.0), Vector(4.0, -1.0, 2.0));
    const Vector point = ray.at(2.5);

    requireVectorsEqual(point, Vector(11.0, -0.5, 8.0));
}
