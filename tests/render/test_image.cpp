#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "render/image.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("setPixel(3, 2) sets the pixel at column 3, row 2 and other pixels remain black", "[camera]") {
    Image img(5, 3);

    REQUIRE(img.getWidth() == 5);
    REQUIRE(img.getHeight() == 3);

    const Colour red(0.8, 0.2, 0.1);
    img.setPixel(3, 2, red);

    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 5; ++x) {
            const Colour& p = img.pixelAt(x, y);
            if (x == 3 && y == 2) {
                REQUIRE_THAT(p.get_r(), WithinAbs(0.8, 1e-6));
                REQUIRE_THAT(p.get_g(), WithinAbs(0.2, 1e-6));
                REQUIRE_THAT(p.get_b(), WithinAbs(0.1, 1e-6));
            } else {
                REQUIRE_THAT(p.get_r(), WithinAbs(0.0, 1e-6));
                REQUIRE_THAT(p.get_g(), WithinAbs(0.0, 1e-6));
                REQUIRE_THAT(p.get_b(), WithinAbs(0.0, 1e-6));
            }
        }
    }
}
