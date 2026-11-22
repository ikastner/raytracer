#pragma once

#include "colour/colour.h"
#include "math/vector.h"

void requireVectorsEqual(const Vector& actual, const Vector& expected, double tolerance = 1e-6);
void requireColoursEqual(const Colour& actual, const Colour& expected, double tolerance = 1e-6);
