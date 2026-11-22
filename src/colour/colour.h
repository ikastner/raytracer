#pragma once

class Colour {
private:
    double r_ = 0.0;
    double g_ = 0.0;
    double b_ = 0.0;

public:
    Colour() = default;
    Colour(double r, double g, double b);

    [[nodiscard]] double get_r() const;
    [[nodiscard]] double get_g() const;
    [[nodiscard]] double get_b() const;

    [[nodiscard]] Colour operator+(const Colour& c) const;
    [[nodiscard]] Colour operator*(const Colour& c) const;
    [[nodiscard]] Colour operator*(double s) const;
};
