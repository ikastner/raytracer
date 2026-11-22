//
// Created by ik on 18/11/2026.
//

#include "colour.h"

Colour::Colour(double r, double g, double b)
    : r_(r), g_(g), b_(b) {
}

double Colour::get_r() const{
    return r_;
}

double Colour::get_g() const{
    return g_;
}

double Colour::get_b() const {
    return b_;
}

Colour Colour::operator+(const Colour& c) const {
    return {r_ + c.r_, g_ + c.g_, b_ + c.b_};
}

Colour Colour::operator*(const Colour& c) const {
    return {r_ * c.r_, g_ * c.g_, b_ * c.b_};
}

Colour Colour::operator*(double s) const {
    return {r_ * s, g_ * s, b_ * s};
};

