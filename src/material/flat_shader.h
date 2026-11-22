#pragma once

#include "material/material.h"

class FlatShader : public Material {
private:
    Colour colour_;

public:
    explicit FlatShader(const Colour& colour);

    [[nodiscard]] Colour shade(const HitInfo& hit, const Light& light) const override;
};
