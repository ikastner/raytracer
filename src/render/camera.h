#pragma once

#include "geometry/ray.h"
#include "math/vector.h"

class Camera {
private:
    Vector position_;
    unsigned int width_ = 1;
    unsigned int height_ = 1;

public:
    explicit Camera(const Vector& position, unsigned int width = 1, unsigned int height = 1);

    [[nodiscard]] const Vector& position() const;

    // Returns a ray starting at the camera position pointing along +Z.
    [[nodiscard]] Ray rayThroughCenter() const;

    // Returns a ray from the camera through pixel (x, y) on the viewport.
    [[nodiscard]] Ray rayForPixel(unsigned int x, unsigned int y) const;
};
