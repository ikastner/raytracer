# 0006 — Use LodePNG for Lossless PNG Image Encoding

## Status

Accepted

## Context

As documented in our [Discovery Report](../discovery/discovery-report.md), the studio needs a deterministic, maintainable, open-source C++ raytracer that runs across 100 CPU-only render-farm machines and partner studios without per-machine licensing fees or complex environment setup. To output rendered frames as lossless PNG files, we need a C/C++ PNG encoding library that is:
1. **100% open source and permissive** (compatible with our MIT licence and partner studio contributions).
2. **Self-contained (zero external system dependencies)** so `make build` works identically in the dev container, CI, and native developer machines without installing external packages like `zlib`.
3. **Simple to isolate** behind our `ImageSaver` / `PngSaver` adapter so core rendering code never depends on third-party library types.

Alternatives considered:

- **`libpng` (PNG Reference Library)** — Industry standard and permissive (`libpng` licence), but requires linking against an external `zlib` installation and uses a verbose, low-level C API (`setjmp`/`longjmp` error handling) that complicates maintenance for a 5-developer team.
- **`libspng` (`spng`)** — Modern, safer C API under BSD-2-Clause, but still requires an external `zlib` or `miniz` dependency.
- **`stb_image_write.h`** — Single-header Public Domain / MIT library with zero dependencies, but relies on preprocessor macro instantiation (`#define STB_IMAGE_WRITE_IMPLEMENTATION`), C-style raw pointers, and produces larger PNG files with less detailed error reporting (`int` return code `0` vs descriptive error codes).
- **`LodePNG`** — Permissive **zlib licence**, zero external dependencies (bundles its own deflate/zlib implementation in pure C++), consists of a single `.h` + `.cpp` pair fetched via CMake `FetchContent`, and provides a native C++ API (`lodepng::encode` accepting `std::vector<unsigned char>`) with explicit numeric error codes and human-readable `lodepng_error_text(error)` diagnostics.

## Decision

Use **LodePNG** (fetched via CMake `FetchContent` and compiled as a library linked `PRIVATE` to our target), wrapped exclusively inside `PngSaver` (`src/output/png_saver.cpp`) behind the `ImageSaver` interface.

## Consequences

**Positive:**
- **Zero external dependencies:** No `zlib` or system packages needed on the 100 render-farm nodes or partner machines.
- **Permissive zlib licence:** 100% free, open source, and compatible with commercial studio production and partner contributions.
- **Native C++ API & diagnosability:** Accepts `std::vector<unsigned char>` directly (no raw `new`/`delete`) and returns clear error messages via `lodepng_error_text`, directly addressing the client's requirement to diagnose failures quickly.
- **Architectural isolation (Adapter pattern):** Only `png_saver.cpp` includes `lodepng.h`; switching to another library or adding OpenEXR (`ExrSaver`) later requires zero changes to `Image`, `Camera`, or `Scene`.

**Negative:**
- Slightly slower encoding speed and larger source file than hardware-tuned `libpng` + `zlib-ng`, though negligible compared to the ~6.6-minute ray-tracing budget per frame.
- Fetched via `FetchContent` on first configure (requires internet access on initial build, like Catch2 in ADR 0003).
