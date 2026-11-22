//
// Created by ik on 18/11/2026.
//

#pragma once

#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include <vector>
#include "colour/colour.h"

class Image {
private:
    unsigned int _width = 0;
    unsigned int _height = 0;
    std::vector<Colour> _pixels;

public:
    Image(unsigned int width, unsigned int height);

    [[nodiscard]]  unsigned int getWidth() const;

    [[nodiscard]]  unsigned int getHeight() const;

    void setPixel(unsigned int x, unsigned int y, const Colour &colour);

    [[nodiscard]] const Colour &pixelAt(unsigned int x, unsigned int y) const;
};


#endif //RAYTRACER_IMAGE_H
