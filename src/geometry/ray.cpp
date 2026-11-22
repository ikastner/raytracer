#include "ray.h"

Ray::Ray(const Vector& origin, const Vector& direction)
    : origin_(origin), direction_(direction) {}

Vector Ray::at(double t) const {
    return origin_ + direction_ * t;
}
