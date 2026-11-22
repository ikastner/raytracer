#include "sphere.h"

#include <cmath>
#include <utility>

namespace {
constexpr double kTMin = 1e-4;
} // namespace

Sphere::Sphere(const Vector& center, double radius, std::shared_ptr<const Material> material)
    : center_(center), radius_(radius), material_(std::move(material)) {}

std::optional<HitInfo> Sphere::isHitBy(const Ray& ray) const {
    const Vector oc = ray.origin() - center_;
    const Vector& d = ray.direction();

    const double a = d.dot(d);
    const double b = 2.0 * oc.dot(d);
    const double c = oc.dot(oc) - radius_ * radius_;

    const double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0) {
        return std::nullopt;
    }

    const double sqrtD = std::sqrt(discriminant);
    double t = (-b - sqrtD) / (2.0 * a);
    if (t <= kTMin) {
        t = (-b + sqrtD) / (2.0 * a);
        if (t <= kTMin) {
            return std::nullopt;
        }
    }

    const Vector point = ray.at(t);
    const Vector normal = (point - center_) * (1.0 / radius_);

    return HitInfo{t, point, normal, material_.get()};
}
