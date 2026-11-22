#include <catch2/catch_test_macros.hpp>

#include "material/flat_shader.h"
#include "material/lambert_shader.h"
#include "test_helpers.h"

TEST_CASE("FlatShader returns its constant colour regardless of light", "[material]") {
    const FlatShader shader(Colour(0.8, 0.3, 0.2));
    const HitInfo hit{2.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0)};
    const Light light(Vector(0.0, -1.0, 0.0), Colour(1.0, 1.0, 1.0));

    requireColoursEqual(shader.shade(hit, light), Colour(0.8, 0.3, 0.2));
}

TEST_CASE("LambertShader scales colour by N dot L and light colour", "[material]") {
    const LambertShader shader(Colour(0.8, 0.4, 0.2));
    const HitInfo hit{2.0, Vector(0.0, 0.0, 0.0), Vector(0.6, 0.8, 0.0)};
    const Light light(Vector(0.0, 1.0, 0.0), Colour(1.0, 0.5, 1.0));

    requireColoursEqual(shader.shade(hit, light), Colour(0.64, 0.16, 0.16));
}

TEST_CASE("LambertShader returns black when surface faces away from light", "[material]") {
    const LambertShader shader(Colour(0.8, 0.4, 0.2));
    const HitInfo hit{2.0, Vector(0.0, 0.0, 0.0), Vector(0.0, -1.0, 0.0)};
    const Light light(Vector(0.0, 1.0, 0.0), Colour(1.0, 0.5, 1.0));

    requireColoursEqual(shader.shade(hit, light), Colour(0.0, 0.0, 0.0));
}
