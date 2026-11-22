#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "math/vector.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("Vector arithmetic and length", "[math]") {
    const Vector a(1.0, 2.0, 3.0);
    const Vector b(4.0, -1.0, 2.0);

    const Vector sum = a + b;
    REQUIRE_THAT(sum.x(), WithinAbs(5.0, 1e-6));
    REQUIRE_THAT(sum.y(), WithinAbs(1.0, 1e-6));
    REQUIRE_THAT(sum.z(), WithinAbs(5.0, 1e-6));

    const Vector diff = a - b;
    REQUIRE_THAT(diff.x(), WithinAbs(-3.0, 1e-6));
    REQUIRE_THAT(diff.y(), WithinAbs(3.0, 1e-6));
    REQUIRE_THAT(diff.z(), WithinAbs(1.0, 1e-6));

    const Vector scaled = 2.0 * a;
    REQUIRE_THAT(scaled.x(), WithinAbs(2.0, 1e-6));
    REQUIRE_THAT(scaled.y(), WithinAbs(4.0, 1e-6));
    REQUIRE_THAT(scaled.z(), WithinAbs(6.0, 1e-6));

    REQUIRE_THAT(a.dot(b), WithinAbs(8.0, 1e-6));

    const Vector v(3.0, 4.0, 0.0);
    REQUIRE_THAT(v.length(), WithinAbs(5.0, 1e-6));

    const Vector unit = v.normalised();
    REQUIRE_THAT(unit.x(), WithinAbs(0.6, 1e-6));
    REQUIRE_THAT(unit.y(), WithinAbs(0.8, 1e-6));
    REQUIRE_THAT(unit.z(), WithinAbs(0.0, 1e-6));
    REQUIRE_THAT(unit.length(), WithinAbs(1.0, 1e-6));
}
