#pragma once

#include <string>

#include "io/image_saver.h"

class PngSaver : public ImageSaver {
private:
    std::string filename_;

public:
    explicit PngSaver(const std::string& filename);

    void save(const Image& img) const override;
};
