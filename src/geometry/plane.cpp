//
// Created by ik on 22/11/2026.
//

#include "plane.h"
#include <cmath>

Plane::Plane(const Vector &point, const Vector &normal)
    : point_(point), normal_(normal.normalised()) {
}

std::optional<HitInfo> Plane::isHitBy(const Ray& ray) const {
    const double denom = ray.direction().dot(normal_);
    if (std::abs(denom) < 1e-9) {
        return std::nullopt;
    }
    const double t = (point_ - ray.origin()).dot(normal_) / denom;
    if (t < 1e-4) {
        return std::nullopt;
    }
    return HitInfo{t, ray.at(t), normal_};
}   