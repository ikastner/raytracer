#include <iostream>

#include "colour/colour.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "io/png_saver.h"
#include "math/vector.h"
#include "render/camera.h"
#include "render/image.h"

int main() {
    const unsigned int width = 400;
    const unsigned int height = 300;
    Image image(width, height);
    Camera camera(Vector(0, 0, -3), width, height);
    Sphere sphere(Vector(0, 0, 0), 1.2);
    Colour colour(1, 1, 1);

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            Ray ray = camera.rayForPixel(x, y);
            auto hit = sphere.isHitBy(ray);
            if (hit.has_value()) {
                image.setPixel(x, y, colour);
            }
        }
    }

    PngSaver saver("output/ma_sphere.png");
    saver.save(image);
    return 0;
}
