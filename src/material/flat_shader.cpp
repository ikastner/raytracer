#include "flat_shader.h"

FlatShader::FlatShader(const Colour& colour) : colour_(colour) {}

Colour FlatShader::shade(const HitInfo&, const Light&) const {
    return colour_;
}
