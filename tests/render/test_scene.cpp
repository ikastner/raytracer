#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <memory>

#include "geometry/plane.h"
#include "geometry/sphere.h"
#include "material/lambert_shader.h"
#include "render/scene.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("Scene::nearestHit returns closest shape regardless of insertion order", "[scene]") {
    const Light sun(Vector(0.0, 1.0, 0.0), Colour(1.0, 1.0, 1.0));
    const Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0));

    Scene nearFirst(sun);
    nearFirst.addShape(std::make_unique<Sphere>(Vector(0.0, 0.0, -3.0), 1.0));
    nearFirst.addShape(std::make_unique<Sphere>(Vector(0.0, 0.0, -7.0), 1.0));
    const auto hitA = nearFirst.nearestHit(ray);
    REQUIRE(hitA.has_value());
    REQUIRE_THAT(hitA->t, WithinAbs(2.0, 1e-6));

    Scene farFirst(sun);
    farFirst.addShape(std::make_unique<Sphere>(Vector(0.0, 0.0, -7.0), 1.0));
    farFirst.addShape(std::make_unique<Sphere>(Vector(0.0, 0.0, -3.0), 1.0));
    const auto hitB = farFirst.nearestHit(ray);
    REQUIRE(hitB.has_value());
    REQUIRE_THAT(hitB->t, WithinAbs(2.0, 1e-6));
}

TEST_CASE("Scene::trace shades lit floor and casts shadow under sphere", "[scene]") {
    const Light sun(Vector(0.0, 1.0, 0.0), Colour(1.0, 1.0, 1.0));
    Scene scene(sun, Colour(0.1, 0.2, 0.3));

    auto floorMat = std::make_shared<LambertShader>(Colour(0.8, 0.8, 0.8));
    auto sphereMat = std::make_shared<LambertShader>(Colour(0.9, 0.2, 0.2));

    scene.addShape(std::make_unique<Plane>(Vector(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0), floorMat));
    scene.addShape(std::make_unique<Sphere>(Vector(0.0, 2.0, -4.0), 1.0, sphereMat));

    // Lit floor away from sphere
    const Ray litRay(Vector(5.0, 0.0, -4.0), Vector(0.0, -1.0, 0.0));
    requireColoursEqual(scene.trace(litRay), Colour(0.8, 0.8, 0.8));

    // Floor directly underneath sphere -> in shadow
    const Ray shadowRay(Vector(0.0, 0.0, -4.0), Vector(0.0, -1.0, 0.0));
    requireColoursEqual(scene.trace(shadowRay), Colour(0.0, 0.0, 0.0));

    // Ray pointing into sky -> background colour
    const Ray skyRay(Vector(5.0, 0.0, -4.0), Vector(0.0, 1.0, 0.0));
    requireColoursEqual(scene.trace(skyRay), Colour(0.1, 0.2, 0.3));
}
