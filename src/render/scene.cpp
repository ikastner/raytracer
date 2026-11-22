#include "scene.h"

#include <limits>
#include <utility>

#include "material/material.h"

Scene::Scene(const Light& light, const Colour& background)
    : light_(light), background_(background) {}

void Scene::addShape(std::unique_ptr<Shape> shape) {
    shapes_.push_back(std::move(shape));
}

std::optional<HitInfo> Scene::nearestHit(const Ray& ray) const {
    std::optional<HitInfo> closest;
    double minT = std::numeric_limits<double>::infinity();

    for (const auto& shape : shapes_) {
        const auto hit = shape->isHitBy(ray);
        if (hit.has_value() && hit->t < minT) {
            minT = hit->t;
            closest = hit;
        }
    }
    return closest;
}

Colour Scene::trace(const Ray& ray) const {
    const auto hit = nearestHit(ray);
    if (!hit.has_value()) {
        return background_;
    }

    const Ray shadowRay(hit->point, light_.direction());
    if (nearestHit(shadowRay).has_value()) {
        return Colour(0.0, 0.0, 0.0);
    }

    if (hit->material == nullptr) {
        return Colour(1.0, 1.0, 1.0);
    }

    return hit->material->shade(*hit, light_);
}
