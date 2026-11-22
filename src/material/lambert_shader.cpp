#include "lambert_shader.h"

#include <algorithm>

LambertShader::LambertShader(const Colour& colour) : colour_(colour) {}

Colour LambertShader::shade(const HitInfo& hit, const Light& light) const {
    const double intensity = std::max(0.0, hit.normal.dot(light.direction()));
    return (colour_ * light.colour()) * intensity;
}
