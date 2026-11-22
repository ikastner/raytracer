#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "colour/colour.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("Colour default and value constructors", "[colour]") {
    const Colour black;
    REQUIRE_THAT(black.get_r(), WithinAbs(0.0, 1e-6));
    REQUIRE_THAT(black.get_g(), WithinAbs(0.0, 1e-6));
    REQUIRE_THAT(black.get_b(), WithinAbs(0.0, 1e-6));

    const Colour c(0.2, 0.5, 0.8);
    REQUIRE_THAT(c.get_r(), WithinAbs(0.2, 1e-6));
    REQUIRE_THAT(c.get_g(), WithinAbs(0.5, 1e-6));
    REQUIRE_THAT(c.get_b(), WithinAbs(0.8, 1e-6));
}

TEST_CASE("Colour addition", "[colour]") {
    const Colour a(0.2, 0.3, 0.4);
    const Colour b(0.1, 0.5, 0.2);
    const Colour sum = a + b;

    REQUIRE_THAT(sum.get_r(), WithinAbs(0.3, 1e-6));
    REQUIRE_THAT(sum.get_g(), WithinAbs(0.8, 1e-6));
    REQUIRE_THAT(sum.get_b(), WithinAbs(0.6, 1e-6));
}

TEST_CASE("Colour scalar multiplication", "[colour]") {
    const Colour c(0.2, 0.4, 0.6);
    const Colour scaled = c * 0.5;

    REQUIRE_THAT(scaled.get_r(), WithinAbs(0.1, 1e-6));
    REQUIRE_THAT(scaled.get_g(), WithinAbs(0.2, 1e-6));
    REQUIRE_THAT(scaled.get_b(), WithinAbs(0.3, 1e-6));
}

TEST_CASE("Colour component-wise multiplication", "[colour]") {
    const Colour a(0.5, 0.2, 0.8);
    const Colour b(0.4, 0.5, 0.25);
    const Colour prod = a * b;

    REQUIRE_THAT(prod.get_r(), WithinAbs(0.2, 1e-6));
    REQUIRE_THAT(prod.get_g(), WithinAbs(0.1, 1e-6));
    REQUIRE_THAT(prod.get_b(), WithinAbs(0.2, 1e-6));
}
