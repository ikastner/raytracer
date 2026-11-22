#pragma once

class Vector {
private:
    double x_ = 0.0;
    double y_ = 0.0;
    double z_ = 0.0;

public:
    Vector() = default;
    Vector(double x, double y, double z);

    [[nodiscard]] double x() const { return x_; }
    [[nodiscard]] double y() const { return y_; }
    [[nodiscard]] double z() const { return z_; }

    [[nodiscard]] double length() const;
    [[nodiscard]] Vector normalised() const;
    [[nodiscard]] double dot(const Vector& other) const;

    [[nodiscard]] Vector operator+(const Vector& other) const;
    [[nodiscard]] Vector operator-(const Vector& other) const;
    [[nodiscard]] Vector operator*(double scalar) const;
};

[[nodiscard]] Vector operator*(double scalar, const Vector& v);
