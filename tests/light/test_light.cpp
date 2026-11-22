#include <catch2/catch_test_macros.hpp>

#include "light/light.h"
#include "test_helpers.h"

TEST_CASE("Light stores normalised direction and colour", "[light]") {
    const Light sun(Vector(3.0, 4.0, 0.0), Colour(1.0, 0.9, 0.8));

    requireVectorsEqual(sun.direction(), Vector(0.6, 0.8, 0.0));
    requireColoursEqual(sun.colour(), Colour(1.0, 0.9, 0.8));
}
