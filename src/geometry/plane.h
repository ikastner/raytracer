#pragma once

#include <memory>

#include "geometry/shape.h"
#include "material/material.h"
#include "math/vector.h"

class Plane : public Shape {
private:
    Vector point_;
    Vector normal_;
    std::shared_ptr<const Material> material_;

public:
    Plane(const Vector& point, const Vector& normal, std::shared_ptr<const Material> material = nullptr);

    [[nodiscard]] std::optional<HitInfo> isHitBy(const Ray& ray) const override;
};
