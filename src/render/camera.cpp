#include "camera.h"

Camera::Camera(const Vector& position, unsigned int width, unsigned int height)
    : position_(position), width_(width), height_(height) {}

const Vector& Camera::position() const {
    return position_;
}

Ray Camera::rayThroughCenter() const {
    const Vector direction(0.0, 0.0, 1.0);
    return Ray(position_, direction);
}

Ray Camera::rayForPixel(unsigned int x, unsigned int y) const {
    const double halfWidth = static_cast<double>(width_) / 2.0;
    const double halfHeight = static_cast<double>(height_) / 2.0;

    const double dx = (static_cast<double>(x) + 0.5 - halfWidth) / halfHeight;
    const double dy = (halfHeight - (static_cast<double>(y) + 0.5)) / halfHeight;

    return Ray(position_, Vector(dx, dy, 1.0));
}
