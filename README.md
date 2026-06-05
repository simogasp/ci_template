# ci_template

[![CI-Build-with-vcpkg](https://github.com/simogasp/ci_template/actions/workflows/build_ci_with_vcpkg.yml/badge.svg)](https://github.com/simogasp/ci_template/actions/workflows/build_ci_with_vcpkg.yml) [![CI-Build-linux-and-macos](https://github.com/simogasp/ci_template/actions/workflows/build_ci_linux_and_macos.yml/badge.svg)](https://github.com/simogasp/ci_template/actions/workflows/build_ci_linux_and_macos.yml) [![CodeQL](https://github.com/simogasp/ci_template/actions/workflows/github-code-scanning/codeql/badge.svg)](https://github.com/simogasp/ci_template/actions/workflows/github-code-scanning/codeql)

A ready-to-use C++ project template with CMake presets, vcpkg dependency management, and GitHub Actions CI already configured.

## Features

- **CMake presets** for debug/release builds, with and without vcpkg
- **vcpkg** integration for cross-platform dependency management with build caching
- **FetchContent** fallback — dependencies are fetched automatically when not found on the system or via vcpkg
- **Catch2** unit testing wired into CTest
- **GitHub Actions** workflows for Linux, macOS, and Windows
- **Dependabot** keeping GitHub Actions versions up to date

## Building

See [BUILD.md](BUILD.md) for full instructions (classic, preset, and vcpkg preset builds).

## Personalising the template

The following files need to be updated when starting a new project from this template.

### `vcpkg.json`

```json
{
  "name": "your-project-name",
  "description": "Your project description",
  "license": "MIT",
  "builtin-baseline": "<vcpkg commit hash>",
  "dependencies": [
    "spdlog",
    "catch2"
  ]
}
```

- **`name`** / **`description`** — set to your project's name and description.
- **`license`** — update to match your chosen license.
- **`builtin-baseline`** — pin the vcpkg commit that provides the library versions you want. Find the latest commit hash at the [vcpkg repository](https://github.com/microsoft/vcpkg).
- **`dependencies`** — replace or extend the list with the libraries your project actually needs.

### `CMakeLists.txt`

```cmake
project(your-project-name VERSION 1.0.0 LANGUAGES CXX)
```

Update the `project()` name and version to match your project.

### `src/main.cpp`

Replace the placeholder `main.cpp` with your application's entry point.

### `tests/simple_test.cpp`

Replace the placeholder test with real unit tests for your code.

### CI workflows (`.github/workflows/`)

Two workflows are provided, covering different dependency strategies:

- **`build_ci_linux_and_macos.yml`** — resolves dependencies from the system package manager (`apt` on Linux, `brew` on macOS). Use this when your dependencies are available as standard system packages. Windows is not supported by this workflow. Caching is handled per package manager: `awalsh128/cache-apt-pkgs-action` for `apt` packages on Linux, and `tecolicom/actions-use-homebrew-tools` for Homebrew packages on macOS.

- **`build_ci_with_vcpkg.yml`** — resolves dependencies via vcpkg, building them from source. Use this for cross-platform builds (Linux, macOS, **and Windows**) or when you need precise version control over your dependencies. Caching covers the vcpkg installation, the built packages (`vcpkg_installed/`), and the vcpkg binary cache (`vcpkg_cache/`) via `actions/cache`, keyed on the OS, `vcpkg.json`, and the workflow file. The vcpkg binary cache is additionally configured via the `VCPKG_BINARY_SOURCES` environment variable so that already-compiled packages are reused across runs.

| File | What to check |
| ---- | ------------- |
| `build_ci_linux_and_macos.yml` | Update the `packages` / `tools` lists if your project needs additional system libraries not covered by vcpkg |
| `build_ci_with_vcpkg.yml` | No changes needed unless you require extra system dependencies |

a template for the ci for c/c++ using vcpkg to build the dependencies and cache
