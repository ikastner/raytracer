# 0005 — Use a Makefile for Short Developer Commands

## Status

Proposed

## Context

Running raw CMake and CTest commands (`cmake -S . -B build`, `cmake --build build`, `cd build && ctest --output-on-failure`) is verbose and repetitive during rapid Red-Green-Refactor TDD cycles. Developers want short, memorable commands similar to `npm run build` or `npm test`.

Alternatives considered:

- **Raw CMake commands** — no extra file, but long to type dozens of times per hour.
- **Shell aliases** — local to one developer's machine and not shared via the repository.

## Decision

Provide a root `Makefile` with four phony targets—`make build`, `make run`, `make test`, and `make clean`—that wrap the underlying CMake and CTest commands, where `run` and `test` automatically depend on `build`.

## Consequences

**Positive:**
- Gives every contributor four simple, memorable commands (`make build`, `make run`, `make test`, `make clean`).
- Used identically by developers locally and by GitHub Actions in CI.

**Negative:**
- `make` is available by default in the Linux dev container and on macOS/Linux, but requires WSL or MinGW if someone works natively on Windows outside the container.
