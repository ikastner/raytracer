# 0004 — Use GitHub Actions for CI

## Status

Accepted

## Context

To prepare the project for internal team handoff and partner studio contributions, every push and pull request needs automated verification that the code compiles cleanly and all unit tests pass inside the reference environment.

Alternatives considered:

- **CircleCI / Travis CI** — require external accounts, third-party permissions, and separate configuration formats outside GitHub.
- **Self-hosted runner** — offers hardware control, but requires maintaining dedicated server infrastructure.

## Decision

Use GitHub Actions (`.github/workflows/ci.yml`) triggered on pushes and pull requests to `main`. Run the job inside the exact same container image as local development (`mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04`) and execute `make build` followed by `make test`.

## Consequences

**Positive:**
- Running inside the dev container image guarantees zero environment drift between local development and CI.
- Built directly into GitHub, free for public repositories, with automatic status checks on pull requests.

**Negative:**
- Couples CI configuration to GitHub Actions syntax.
- Downloading the container image and compiling Catch2 via `FetchContent` adds execution time to each CI run unless build caching is added later.
