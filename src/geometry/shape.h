#pragma once

#include <optional>

#include "geometry/hit_info.h"
#include "geometry/ray.h"

class Shape {
public:
    virtual ~Shape() = default;

    // Returns a HitInfo with t > 1e-4 and a unit-length normal, or std::nullopt if missed.
    [[nodiscard]] virtual std::optional<HitInfo> isHitBy(const Ray& ray) const = 0;
};
