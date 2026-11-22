#pragma once

#include "math/vector.h"

class Material;

struct HitInfo {
    double t = 0.0;
    Vector point;
    Vector normal;
    const Material* material = nullptr;
};
