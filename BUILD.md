# Building the Project

## Prerequisites

- **CMake** ≥ 3.10 (≥ 3.19 required when using presets)
- A C++17-compatible compiler (GCC, Clang, MSVC)
- **vcpkg** (only for the vcpkg-based build — see [section 3](#3-cmake-presets-with-vcpkg))

### Dependencies

| Library | Purpose | Version (FetchContent fallback) |
| ------- | ------- | -------------------------------- |
| [spdlog](https://github.com/gabime/spdlog) | Logging | v1.16.0 |
| [Catch2](https://github.com/catchorg/Catch2) | Unit testing | v3.11.0 |

When dependencies are not found on the system (or not provided by vcpkg), CMake will download and build them automatically via `FetchContent`.

---

## 1. Classic Build (no presets)

This is the standard out-of-source build workflow.

### Configure and build

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

#### Build type

Pass `-DCMAKE_BUILD_TYPE` to select the build configuration:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake .. -DCMAKE_BUILD_TYPE=Debug     # default if omitted
```

#### Disable tests

Tests are built by default. To skip them:

```bash
cmake .. -DBUILD_TESTS=OFF
```

### Run the tests

From inside the build directory:

```bash
ctest
# or
cmake --build . --target test
```

---

## 2. CMake Presets (without vcpkg)

Requires **CMake ≥ 3.19**. The presets are defined in [`CMakePresets.json`](CMakePresets.json). Dependencies are resolved from the system or downloaded via `FetchContent` if not found.

### Available presets

| Preset | Build type | Binary directory |
| ------ | ---------- | ---------------- |
| `debug` | Debug | `build/debug/` |
| `release` | Release | `build/release/` |

### Configure, build, and test

```bash
# Debug
cmake --preset debug
cmake --build --preset debug
ctest --preset debug  # or: cmake --build --preset debug --target test

# Release
cmake --preset release
cmake --build --preset release
ctest --preset release  # or: cmake --build --preset release --target test
```

---

## 3. CMake Presets with vcpkg

Requires **CMake ≥ 3.19** and a working [vcpkg](https://vcpkg.io) installation. vcpkg handles all dependencies declared in [`vcpkg.json`](vcpkg.json) (`spdlog`, `catch2`) without relying on `FetchContent` or system packages.

### Install vcpkg

If you do not already have vcpkg, clone it and bootstrap it:

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg && ./bootstrap-vcpkg.sh   # on Windows: .\bootstrap-vcpkg.bat
```

Set the `VCPKG_ROOT` environment variable to the vcpkg directory:

```bash
export VCPKG_ROOT=/path/to/vcpkg   # bash / zsh
# or
set VCPKG_ROOT=C:\path\to\vcpkg    # Windows cmd
```

### Available presets

| Preset | Build type | Binary directory |
| ------ | ---------- | ---------------- |
| `vcpkg-debug` | Debug | `build/vcpkg-debug/` |
| `vcpkg-release` | Release | `build/vcpkg-release/` |

vcpkg packages are installed into `vcpkg_installed/` at the project root (configured via `VCPKG_INSTALLED_DIR` in the preset).

### Configure, build, and test

```bash
# Debug
cmake --preset vcpkg-debug
cmake --build --preset vcpkg-debug
ctest --preset vcpkg-debug  # or: cmake --build --preset vcpkg-debug --target test

# Release
cmake --preset vcpkg-release
cmake --build --preset vcpkg-release
ctest --preset vcpkg-release  # or: cmake --build --preset vcpkg-release --target test
```

> **Note:** On the first run vcpkg will download and compile the declared dependencies. Subsequent runs use the local cache and are much faster.
