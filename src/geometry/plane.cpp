#include "plane.h"

#include <cmath>
#include <utility>

namespace {
constexpr double kParallelEps = 1e-6;
constexpr double kTMin = 1e-4;
} // namespace

Plane::Plane(const Vector& point, const Vector& normal, std::shared_ptr<const Material> material)
    : point_(point), normal_(normal.normalised()), material_(std::move(material)) {}

std::optional<HitInfo> Plane::isHitBy(const Ray& ray) const {
    const double denom = ray.direction().dot(normal_);
    if (std::abs(denom) < kParallelEps) {
        return std::nullopt;
    }

    const double t = (point_ - ray.origin()).dot(normal_) / denom;
    if (t <= kTMin) {
        return std::nullopt;
    }

    // Flip normal so it always faces against the incoming ray on double-sided planes.
    const Vector hitNormal = denom > 0.0 ? normal_ * -1.0 : normal_;
    return HitInfo{t, ray.at(t), hitNormal, material_.get()};
}
