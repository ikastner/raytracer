//
// Created by ik on 22/11/2026.
//

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H
#include "shape.h"
#include "math/vector.h"


class Plane : public Shape {
private:
    Vector point_;
    Vector normal_;

public:
    Plane (const Vector &point, const Vector &normal);
    [[nodiscard]] std::optional<HitInfo> isHitBy(const Ray& ray) const override;
};


#endif //RAYTRACER_PLANE_H
