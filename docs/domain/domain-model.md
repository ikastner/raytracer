# Domain Model — Raytracer (`m1`)

This diagram maps the core domain concepts of the raytracer and their relationships, reflecting the `m1` architecture (a ball lit by the sun on a floor).

```mermaid
classDiagram
    class Vector {
        -double x_
        -double y_
        -double z_
        +length() double
        +normalised() Vector
        +dot(Vector) double
    }

    class Colour {
        -double r_
        -double g_
        -double b_
        +get_r() double
        +get_g() double
        +get_b() double
    }

    class Ray {
        -Vector origin_
        -Vector direction_
        +origin() Vector
        +direction() Vector
        +at(double t) Vector
    }

    class HitInfo {
        +double t
        +Vector point
        +Vector normal
        +const Material* material
    }

    class Shape {
        <<interface>>
        +isHitBy(Ray) optional~HitInfo~
    }

    class Sphere {
        -Vector center_
        -double radius_
        -shared_ptr~Material~ material_
        +isHitBy(Ray) optional~HitInfo~
    }

    class Plane {
        -Vector point_
        -Vector normal_
        -shared_ptr~Material~ material_
        +isHitBy(Ray) optional~HitInfo~
    }

    class Light {
        -Vector direction_
        -Colour colour_
        +direction() Vector
        +colour() Colour
    }

    class Material {
        <<interface>>
        +shade(HitInfo, Light) Colour
    }

    class FlatShader {
        -Colour colour_
        +shade(HitInfo, Light) Colour
    }

    class LambertShader {
        -Colour colour_
        +shade(HitInfo, Light) Colour
    }

    class Scene {
        -vector~unique_ptr~Shape~~ shapes_
        -Light light_
        -Colour background_
        +addShape(unique_ptr~Shape~)
        +nearestHit(Ray) optional~HitInfo~
        +trace(Ray) Colour
    }

    class Camera {
        -Vector position_
        -unsigned int width_
        -unsigned int height_
        +rayThroughCenter() Ray
        +rayForPixel(x, y) Ray
    }

    class Image {
        -unsigned int width_
        -unsigned int height_
        -vector~Colour~ pixels_
        +setPixel(x, y, Colour)
        +pixelAt(x, y) Colour
    }

    class ImageSaver {
        <<interface>>
        +save(Image)
    }

    class PngSaver {
        -string filename_
        +save(Image)
    }

    Shape <|.. Sphere
    Shape <|.. Plane
    Material <|.. FlatShader
    Material <|.. LambertShader
    ImageSaver <|.. PngSaver

    Ray *-- Vector
    Sphere o-- Material
    Plane o-- Material
    Scene *-- Shape : owns
    Scene *-- Light
    Camera ..> Ray : creates
    Image *-- Colour
    PngSaver ..> Image : reads
```

## Key Design Decisions

- **Composition over inheritance:** `Sphere` and `Plane` each hold a `Material` rather than creating shape × material inheritance hierarchies.
- **Open/Closed & Dependency Inversion:** `Scene` depends only on the `Shape` and `Material` interfaces; `main.cpp` acts as the single Composition Root wiring concrete classes (`Sphere`, `Plane`, `LambertShader`, `PngSaver`).
- **Adapter & Strategy patterns:** `PngSaver` isolates LodePNG behind `ImageSaver`, and `Material` allows swapping shading strategies (`FlatShader`, `LambertShader`) without modifying `Scene`.
