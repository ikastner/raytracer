#include "light.h"

Light::Light(const Vector& direction, const Colour& colour)
    : direction_(direction.normalised()), colour_(colour) {}

const Vector& Light::direction() const {
    return direction_;
}

const Colour& Light::colour() const {
    return colour_;
}
