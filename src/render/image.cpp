#include "image.h"

Image::Image(unsigned int width, unsigned int height)
    : _width(width), _height(height), _pixels(width * height) {}

unsigned int Image::getWidth() const {
    return _width;
}

unsigned int Image::getHeight() const {
    return _height;
}

void Image::setPixel(unsigned int x, unsigned int y, const Colour& colour) {
    _pixels[y * _width + x] = colour;
}

const Colour& Image::pixelAt(unsigned int x, unsigned int y) const {
    return _pixels[y * _width + x];
}
