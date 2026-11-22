# 0007 — Organise Source and Tests by Domain Folder

## Status

Accepted

## Context

As the raytracer grows (vectors, rays, spheres, planes, colours, lights, materials, camera, image, and PNG output), keeping all files flat in `src/` or splitting single classes into one-file folders (`src/ray/`) makes navigation harder and risks creating circular dependencies between modules.

Alternatives considered:

- **Flat `src/` and `tests/` directories** — simple at the start, but becomes cluttered once lighting, materials, scenes, and multiple shapes are added.
- **Technical layers (`models/`, `services/`, `utils/`)** — hides the raytracing domain vocabulary and encourages god-folders like `utils/`.
- **Domain folders with acyclic dependencies** — group files by domain responsibility (`math/`, `colour/`, `geometry/`, `light/`, `material/`, `render/`, `io/`) and mirror the same folders under `tests/`.

## Decision

Organise `src/` into domain folders with one-way (acyclic) dependencies:

- `src/math/` — mathematical primitives (`vector.h`, `vector.cpp`)
- `src/colour/` — colour representation (`colour.h`, `colour.cpp`)
- `src/geometry/` — rays, hit records, and shapes (`ray.*`, `hit_info.h`, `sphere.*`)
- `src/light/` — light sources (`light.*`)
- `src/material/` — shading interfaces and implementations (`material.h`, `flat_shader.*`, `lambert_shader.*`)
- `src/render/` — image buffer and camera (`image.*`, `camera.*`)
- `src/io/` — image output adapters (`image_saver.h`, `png_saver.*`)

Mirror this folder layout under `tests/` (`tests/colour/`, `tests/geometry/`, `tests/light/`, `tests/material/`, `tests/math/`, `tests/render/`), with shared floating-point assertion helpers in `tests/test_helpers.h/.cpp`.

## Consequences

**Positive:**
- Clear separation of concerns matching the domain model and preventing circular includes (`io/` depends on `render/image.h` without touching `geometry/` or `material/`).
- Every test file maps 1-to-1 to its source folder, making it easy for internal developers and partner studios to locate code and tests.

**Negative:**
- Moving existing files (`src/ray/` → `src/geometry/`, `src/output/` → `src/io/`, and `tests/`) requires updating `#include` paths and `CMakeLists.txt` once.
