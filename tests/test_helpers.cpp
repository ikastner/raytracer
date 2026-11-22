#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using Catch::Matchers::WithinAbs;

void requireVectorsEqual(const Vector& actual, const Vector& expected, double tolerance) {
    REQUIRE_THAT(actual.x(), WithinAbs(expected.x(), tolerance));
    REQUIRE_THAT(actual.y(), WithinAbs(expected.y(), tolerance));
    REQUIRE_THAT(actual.z(), WithinAbs(expected.z(), tolerance));
}

void requireColoursEqual(const Colour& actual, const Colour& expected, double tolerance) {
    REQUIRE_THAT(actual.get_r(), WithinAbs(expected.get_r(), tolerance));
    REQUIRE_THAT(actual.get_g(), WithinAbs(expected.get_g(), tolerance));
    REQUIRE_THAT(actual.get_b(), WithinAbs(expected.get_b(), tolerance));
}
