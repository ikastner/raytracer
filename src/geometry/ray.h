#pragma once

#include "math/vector.h"

class Ray {
private:
    Vector origin_;
    Vector direction_;

public:
    Ray(const Vector& origin, const Vector& direction);

    [[nodiscard]] const Vector& origin() const { return origin_; }
    [[nodiscard]] const Vector& direction() const { return direction_; }

    // Returns the point along the ray at parameter t: origin + t * direction.
    [[nodiscard]] Vector at(double t) const;
};
