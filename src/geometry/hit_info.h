#pragma once

#include "math/vector.h"

struct HitInfo {
    double t = 0.0;
    Vector point;
    Vector normal;
};
