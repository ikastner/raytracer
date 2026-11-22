#include "png_saver.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

#include "lodepng.h"

namespace {
unsigned char toByte(double channel) {
    const double clamped = std::clamp(channel, 0.0, 1.0);
    return static_cast<unsigned char>(std::round(clamped * 255.0));
}
} // namespace

PngSaver::PngSaver(const std::string& filename) : filename_(filename) {}

void PngSaver::save(const Image& img) const {
    const unsigned int width = img.getWidth();
    const unsigned int height = img.getHeight();
    std::vector<unsigned char> buffer(width * height * 4);

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            const Colour& c = img.pixelAt(x, y);
            const std::size_t idx = 4 * (y * width + x);
            buffer[idx + 0] = toByte(c.get_r());
            buffer[idx + 1] = toByte(c.get_g());
            buffer[idx + 2] = toByte(c.get_b());
            buffer[idx + 3] = 255;
        }
    }

    const unsigned int error = lodepng::encode(filename_, buffer, width, height);
    if (error != 0) {
        throw std::runtime_error(std::string("PNG encode error: ") + lodepng_error_text(error));
    }
}
