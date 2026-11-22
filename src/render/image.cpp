#include "image.h"

Image::Image(unsigned int width, unsigned int height)
    : width_(width), height_(height), pixels_(width * height) {}

unsigned int Image::getWidth() const {
    return width_;
}

unsigned int Image::getHeight() const {
    return height_;
}

void Image::setPixel(unsigned int x, unsigned int y, const Colour& colour) {
    pixels_[y * width_ + x] = colour;
}

const Colour& Image::pixelAt(unsigned int x, unsigned int y) const {
    return pixels_[y * width_ + x];
}
