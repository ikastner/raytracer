#pragma once

#include "colour/colour.h"
#include "math/vector.h"

class Light {
private:
    Vector direction_;
    Colour colour_;

public:
    // Constructs a directional light; direction is stored normalised (unit length).
    Light(const Vector& direction, const Colour& colour);

    [[nodiscard]] const Vector& direction() const;
    [[nodiscard]] const Colour& colour() const;
};
