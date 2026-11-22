//
// Created by ik on 18/11/2026.
//
#pragma once

#ifndef RAYTRACER_COLOUR_H
#define RAYTRACER_COLOUR_H


class Colour {
private:
    double r_ = 0.0;
    double g_ = 0.0;
    double b_ = 0.0;

public:
    Colour(double r, double g, double b);

    Colour() = default;

    [[nodiscard]] double get_r() const;

    [[nodiscard]] double get_g() const;

    [[nodiscard]] double get_b() const;

    Colour operator+(const Colour &c) const;

    Colour operator*(const Colour &c) const;

    Colour operator*(double s) const;
};


#endif //RAYTRACER_COLOUR_H
