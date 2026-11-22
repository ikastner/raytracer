#pragma once

#include <optional>

#include "geometry/hit_info.h"
#include "geometry/ray.h"
#include "math/vector.h"

class Sphere {
private:
    Vector center_;
    double radius_ = 0.0;

public:
    Sphere(const Vector& center, double radius);

    [[nodiscard]] const Vector& center() const { return center_; }
    [[nodiscard]] double radius() const { return radius_; }

    // Returns a HitInfo with t > 1e-4 and a unit-length normal, or std::nullopt if missed.
    [[nodiscard]] std::optional<HitInfo> isHitBy(const Ray& ray) const;
};
