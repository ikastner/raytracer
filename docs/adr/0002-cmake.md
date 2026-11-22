# 0002 — Use CMake (with CTest)

## Status

Proposed

## Context

The raytracer must build consistently across Linux, macOS, and Windows, integrate with IDEs (VS Code, CLion, Zed) and terminal workflows, and download test dependencies automatically without requiring a separate system package manager.

Alternatives considered:

- **Plain GNU Make** — simple, but not natively cross-platform on Windows and lacks automatic IDE target discovery.
- **Meson** — fast and modern, but less widely supported by C++ IDEs and less familiar in traditional 3D production pipelines.
- **Bazel** — powerful for huge monorepos, but introduces heavy setup and learning overhead for a focused project.

## Decision

Use CMake (minimum version 3.20) with `CMAKE_CXX_STANDARD 20` as the build generator, paired with CTest for running tests. Use CMake's `FetchContent` module to pull Catch2 automatically at configure time, and `catch_discover_tests` to register unit tests with CTest.

## Consequences

**Positive:**
- Works natively with CLion, VS Code (CMake Tools), Zed, and the command line across all platforms.
- `FetchContent` keeps the repository self-contained without requiring Conan, vcpkg, or manual library installation.
- CTest provides a standard test runner command (`ctest --output-on-failure`).

**Negative:**
- CMake has its own scripting syntax that the team must understand and maintain.
- `FetchContent` requires internet access on the first configure (and after `make clean`) to download Catch2.
