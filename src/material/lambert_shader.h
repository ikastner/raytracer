#pragma once

#include "material/material.h"

class LambertShader : public Material {
private:
    Colour colour_;

public:
    explicit LambertShader(const Colour& colour);

    [[nodiscard]] Colour shade(const HitInfo& hit, const Light& light) const override;
};
