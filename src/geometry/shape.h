//
// Created by ik on 22/11/2026.
//

#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H

#pragma once
#include <optional>

#include "geometry/hit_info.h"
#include "geometry/ray.h"

class Shape {
public:
    virtual ~Shape() = default;

    [[nodiscard]] virtual std::optional<HitInfo> isHitBy(const Ray &ray) const = 0;
};


#endif //RAYTRACER_SHAPE_H
