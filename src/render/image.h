#pragma once

#include <vector>

#include "colour/colour.h"

class Image {
private:
    unsigned int width_ = 0;
    unsigned int height_ = 0;
    std::vector<Colour> pixels_;

public:
    Image(unsigned int width, unsigned int height);

    [[nodiscard]] unsigned int getWidth() const;
    [[nodiscard]] unsigned int getHeight() const;

    void setPixel(unsigned int x, unsigned int y, const Colour& colour);
    [[nodiscard]] const Colour& pixelAt(unsigned int x, unsigned int y) const;
};
