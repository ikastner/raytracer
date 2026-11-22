# 0001 — Use a Dev Container

## Status

Accepted

## Context

Contributors join the project on Windows, macOS, and Linux, each with different compiler versions and tool installations. Without a shared environment, differences in GCC/Clang versions, CMake versions, or missing tools cause "works on my machine" failures across the studio and partner studios.

Alternatives considered:

- **Native setup with documented prerequisites** — lower tooling overhead, but requires every contributor to install and version-match a C++20 compiler, CMake ≥ 3.20, and Git manually. Prone to drift across different laptops.
- **CI-only standardisation** — catches integration problems on pull requests but does not help developers during local TDD loops.

## Decision

Provide a `.devcontainer/devcontainer.json` backed by `mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04`. VS Code and Zed open the project inside this container automatically, and `postCreateCommand` configures and builds the project on first launch.

## Consequences

**Positive:**
- Every developer and partner contributor uses the exact same Linux environment, compiler, CMake version, and Git.
- New contributors are productive within minutes of cloning the repository.

**Negative:**
- Requires Docker to be installed and running on every developer's machine.
- First container startup adds a one-time download and build delay.
- Developers using a native IDE (like CLion on macOS) must ensure their local CMake/compiler versions match C++20.
