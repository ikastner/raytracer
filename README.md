# Raytracer

A C++20 raytracer built incrementally using Test-Driven Development (TDD).

[![CI](https://github.com/ikastner/raytracer/actions/workflows/ci.yml/badge.svg)](https://github.com/ikastner/raytracer/actions/workflows/ci.yml)

Licence: [MIT](LICENSE) · [Contributing](CONTRIBUTING.md) · [Code of Conduct](CODE_OF_CONDUCT.md) · [Discovery Report (`m0`)](docs/discovery/discovery-report.md) · [ADRs](docs/adr/)

---

## Project structure

```text
.
├── .devcontainer/          # Dev container config (VS Code / Zed)
├── .github/                # CI workflow, PR and Issue templates
├── docs/
│   ├── adr/                # Architecture Decision Records
│   └── discovery/          # Milestone m0 Discovery Report
├── src/
│   ├── main.cpp            # Main entry point (Composition Root)
│   ├── Vector3.h           # 3D Vector interface
│   └── Vector3.cpp         # 3D Vector implementation
├── tests/
│   └── test_main.cpp       # Catch2 unit tests
├── AGENTS.md               # Engineering & TDD rules for AI assistants
├── CLAUDE.md               # Entry point pointing to AGENTS.md
├── CMakeLists.txt          # Cross-platform CMake build configuration
└── Makefile                # Short commands (build, run, test, clean)
```

---

## Cross-platform setup

### Option A — Dev container (recommended)

Requires [Docker](https://www.docker.com/) and either:
- **VS Code** with the [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension, or
- **Zed** with its built-in dev container support.

1. Open the repository folder in VS Code or Zed.
2. When prompted, click **"Reopen in Container"** (VS Code) or **"Use Dev Container"** (Zed).
3. The container image provides GCC, CMake ≥ 3.20, and Git. Catch2 is downloaded automatically at first build.
4. CMake configures and builds automatically on container creation (`postCreateCommand`).

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
| `make build` | Configure + compile everything |
| `make run` | Build then launch the raytracer |
| `make test` | Build then run the Catch2 test suite via CTest |
| `make clean` | Delete the `build/` directory |

`run` and `test` both depend on `build`, so they recompile automatically if sources have changed.

---

## Test-driven development workflow

Tests live in `tests/`. Add a new `TEST_CASE` before writing the implementation, confirm it fails (`make test`), then implement the minimal code until it passes.

| Macro | Purpose |
|-------|---------|
| `REQUIRE(expr)` | Assert; stop test on failure |
| `CHECK(expr)` | Assert; continue on failure |
| `REQUIRE_THROWS(expr)` | Expect an exception |
| `Catch::Approx(x).epsilon(e)` | Floating-point comparison |
