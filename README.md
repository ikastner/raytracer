# Raytracer

A C++20 raytracer built incrementally using Test-Driven Development (TDD).

[![CI](https://github.com/ikastner/raytracer/actions/workflows/ci.yml/badge.svg)](https://github.com/ikastner/raytracer/actions/workflows/ci.yml)

Licence: [MIT](LICENSE) · [Contributing](CONTRIBUTING.md) · [Code of Conduct](CODE_OF_CONDUCT.md) · [Discovery Report (`m0`)](docs/discovery/discovery-report.md) · [Domain Model (`m1`)](docs/domain/domain-model.md) · [ADRs](docs/adr/)

---

## Project structure

```text
.
├── .devcontainer/          # Dev container config (VS Code / Zed / CLion)
├── .github/                # CI workflow, PR and Issue templates
├── docs/
│   ├── adr/                # Architecture Decision Records (0001–0007)
│   ├── discovery/          # Milestone m0 Discovery Report
│   └── domain/             # Milestone m1 Domain Model (Mermaid)
├── src/
│   ├── colour/             # Colour value object
│   ├── geometry/           # Shape interface, Sphere, Plane, Ray, HitInfo
│   ├── io/                 # ImageSaver interface & PngSaver (LodePNG adapter)
│   ├── light/              # Directional Light (sun)
│   ├── material/           # Material interface, FlatShader, LambertShader
│   ├── math/               # Vector value object
│   ├── render/             # Camera, Image, Scene (tracing & shadows)
│   └── main.cpp            # Composition Root (renders output/m1_scene.png)
├── tests/                  # Catch2 unit test suite mirroring src/
├── AGENTS.md               # Engineering & TDD rules for AI assistants
├── CLAUDE.md               # Entry point pointing to AGENTS.md
├── CMakeLists.txt          # Cross-platform CMake build configuration
└── Makefile                # Short commands (build, run, test, clean)
```

---

## Cross-platform setup

### Option A — Dev container (recommended)

Requires [Docker](https://www.docker.com/) and either:
- **VS Code** with the [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension,
- **Zed** with its built-in dev container support, or
- **CLion** via *File → Connect to Remote → Dev Containers*.

### Option B — Native (macOS / Linux / Windows)

| Tool | Minimum version |
|------|----------------|
| CMake | 3.20 |
| C++ compiler | GCC 12 / Clang 15 / MSVC 19.34 (C++20) |
| Git | any recent |

---

## Common commands

| Command | What it does |
|---------|-------------|
| `make build` | Configure + compile everything (`-Wall -Wextra -Wpedantic`) |
| `make run` | Build and render `output/m1_scene.png` |
| `make test` | Build and run the Catch2 test suite via CTest |
| `make clean` | Delete the `build/` directory |
