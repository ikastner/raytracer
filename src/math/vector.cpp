#include "vector.h"

#include <cmath>

Vector::Vector(double x, double y, double z) : x_(x), y_(y), z_(z) {}

double Vector::length() const {
    return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

Vector Vector::normalised() const {
    const double len = length();
    if (len == 0.0) {
        return {};
    }
    return {x_ / len, y_ / len, z_ / len};
}

double Vector::dot(const Vector& other) const {
    return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
}

Vector Vector::operator+(const Vector& other) const {
    return {x_ + other.x_, y_ + other.y_, z_ + other.z_};
}

Vector Vector::operator-(const Vector& other) const {
    return {x_ - other.x_, y_ - other.y_, z_ - other.z_};
}

Vector Vector::operator*(double scalar) const {
    return {x_ * scalar, y_ * scalar, z_ * scalar};
}

Vector operator*(double scalar, const Vector& v) {
    return v * scalar;
}
