#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "colour/colour.h"
#include "geometry/hit_info.h"
#include "geometry/ray.h"
#include "geometry/shape.h"
#include "light/light.h"

class Scene {
private:
    std::vector<std::unique_ptr<Shape>> shapes_;
    Light light_;
    Colour background_;

public:
    explicit Scene(const Light& light, const Colour& background = Colour(0.0, 0.0, 0.0));

    void addShape(std::unique_ptr<Shape> shape);

    // Returns the closest intersection (smallest t > 1e-4) across all shapes, or std::nullopt.
    [[nodiscard]] std::optional<HitInfo> nearestHit(const Ray& ray) const;

    // Traces a ray through the scene and returns the shaded pixel colour (including shadows).
    [[nodiscard]] Colour trace(const Ray& ray) const;
};
