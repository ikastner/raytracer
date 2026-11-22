#include <filesystem>
#include <iostream>
#include <memory>

#include "colour/colour.h"
#include "geometry/plane.h"
#include "geometry/sphere.h"
#include "io/png_saver.h"
#include "light/light.h"
#include "material/lambert_shader.h"
#include "math/vector.h"
#include "render/camera.h"
#include "render/image.h"
#include "render/scene.h"

int main() {
    constexpr unsigned int width = 1920;
    constexpr unsigned int height = 1080;

    if (std::filesystem::exists("../CMakeLists.txt")) {
        std::filesystem::current_path("..");
    }
    std::filesystem::create_directories("output");

    const Light sun(Vector(-1.0, 1.5, -1.0), Colour(1.0, 1.0, 0.95));
    Scene scene(sun, Colour(0.45, 0.65, 0.95));

    auto sphereMaterial = std::make_shared<LambertShader>(Colour(0.9, 0.25, 0.2));
    auto floorMaterial = std::make_shared<LambertShader>(Colour(0.75, 0.75, 0.75));

    scene.addShape(std::make_unique<Sphere>(Vector(0.0, 0.0, 1.0), 1.0, sphereMaterial));
    scene.addShape(std::make_unique<Plane>(Vector(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0), floorMaterial));

    const Camera camera(Vector(0.0, 0.5, -3.0), width, height);
    Image img(width, height);

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            img.setPixel(x, y, scene.trace(camera.rayForPixel(x, y)));
        }
    }

    const PngSaver saver("output/m1_scene.png");
    saver.save(img);
    std::cout << "Rendered output/m1_scene.png (" << width << "x" << height << ")\n";
    return 0;
}
