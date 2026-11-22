#pragma once

#include "colour/colour.h"
#include "geometry/hit_info.h"
#include "light/light.h"

class Material {
public:
    virtual ~Material() = default;

    // Computes the shaded colour at a hit point (expects unit-length normal and light direction).
    [[nodiscard]] virtual Colour shade(const HitInfo& hit, const Light& light) const = 0;
};
