#pragma once

#include "render/image.h"

class ImageSaver {
public:
    virtual ~ImageSaver() = default;

    // Saves the given image to its destination; throws on I/O or encoding failure.
    virtual void save(const Image& img) const = 0;
};
