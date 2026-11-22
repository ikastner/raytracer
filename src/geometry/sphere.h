#pragma once

#include <memory>
#include <optional>

#include "geometry/shape.h"
#include "material/material.h"
#include "math/vector.h"

class Sphere : public Shape {
private:
    Vector center_;
    double radius_ = 0.0;
    std::shared_ptr<const Material> material_;

public:
    Sphere(const Vector& center, double radius, std::shared_ptr<const Material> material = nullptr);

    [[nodiscard]] const Vector& center() const { return center_; }
    [[nodiscard]] double radius() const { return radius_; }

    [[nodiscard]] std::optional<HitInfo> isHitBy(const Ray& ray) const override;
};
