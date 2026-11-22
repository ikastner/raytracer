#include <catch2/catch_test_macros.hpp>

#include "render/camera.h"
#include "test_helpers.h"

TEST_CASE("Ray through center has camera position as origin", "[camera]") {
    const Camera camera(Vector(0.0, 0.0, -1.0));
    const Ray ray = camera.rayThroughCenter();

    requireVectorsEqual(ray.origin(), Vector(0.0, 0.0, -1.0));
    requireVectorsEqual(ray.direction(), Vector(0.0, 0.0, 1.0));
}

TEST_CASE("Ray through center always points in +Z direction", "[camera]") {
    const Camera camera(Vector(1.0, 2.0, 1.0));
    const Ray ray = camera.rayThroughCenter();

    requireVectorsEqual(ray.origin(), Vector(1.0, 2.0, 1.0));
    requireVectorsEqual(ray.direction(), Vector(0.0, 0.0, 1.0));
}

TEST_CASE("Camera::rayForPixel computes rays for odd 5x3 image", "[camera]") {
    const Camera camera(Vector(0.0, 0.0, -2.0), 5, 3);

    const Ray centerRay = camera.rayForPixel(2, 1);
    requireVectorsEqual(centerRay.origin(), Vector(0.0, 0.0, -2.0));
    requireVectorsEqual(centerRay.direction(), Vector(0.0, 0.0, 1.0));

    const Ray topLeftRay = camera.rayForPixel(0, 0);
    requireVectorsEqual(topLeftRay.direction(), Vector(-4.0 / 3.0, 2.0 / 3.0, 1.0));
}
