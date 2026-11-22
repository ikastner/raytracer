#include <catch2/catch_test_macros.hpp>

#include <array>
#include <cstdio>
#include <fstream>

#include "io/png_saver.h"

TEST_CASE("PngSaver writes a valid PNG file to disk", "[output]") {
    const std::string path = "test_output_3x5.png";
    std::remove(path.c_str());

    Image img(3, 5);
    img.setPixel(2, 4, Colour(0.8, 0.2, 0.1));

    const PngSaver saver(path);
    saver.save(img);

    std::ifstream file(path, std::ios::binary);
    REQUIRE(file.is_open());

    std::array<unsigned char, 8> header{};
    file.read(reinterpret_cast<char*>(header.data()), header.size());
    REQUIRE(file.gcount() == 8);

    const std::array<unsigned char, 8> expectedPngSignature{
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A
    };
    REQUIRE(header == expectedPngSignature);

    file.close();
    std::remove(path.c_str());
}
