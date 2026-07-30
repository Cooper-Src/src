# Contributing to src

Thank you for your interest in contributing to **src**.

Whether you're fixing bugs, improving documentation, implementing new features, or reporting issues, your contributions are welcome.

---

# Before You Start

Please read the documentation before contributing.

Useful resources

* README.md
* docs/architecture.md
* docs/commands.md
* docs/manifest-spec.md
* docs/registry.md
* docs/source-types.md

Understanding the architecture before making changes will help keep the project consistent.

---

# Project Goals

`src` is designed to be

* lightweight
* source-first
* predictable
* easy to maintain
* easy to extend

Features that increase unnecessary complexity are unlikely to be accepted.

---

# Development Setup

## Requirements

* CMake 3.20+
* C++20 compiler
* Visual Studio Build Tools (MSVC)
* vcpkg

Required libraries

* curl
* cJSON
* libarchive (or the configured extraction library)

---

# Building

Configure

```bash id="tlxyk4"
cmake --preset default
```

Build

```bash id="vwtk2u"
cmake --build build --config Release
```

---

# Coding Style

## General

* Use modern C++20.
* Prefer the standard library over third-party libraries.
* Keep implementations simple.
* Avoid unnecessary abstractions.

---

## Naming

Classes

```cpp id="5a2o6x"
PackageDownloader
RegistryManager
ManifestParser
```

Functions

```cpp id="nlnjlwm"
installPackage()
updateRegistry()
parseManifest()
```

Variables

```cpp id="1zc2m4"
packageName
downloadUrl
installPath
```

Constants

```cpp id="1kqjlwm"
constexpr
```

should be preferred where appropriate.

---

## Formatting

Use four spaces for indentation.

Always use braces.

Preferred

```cpp id="h74nnd"
if (success)
{
    install();
}
```

Avoid

```cpp id="qujjlwm"
if (success)
    install();
```

---

# Pull Requests

Good pull requests

* solve one problem
* remain focused
* include documentation updates when necessary
* build successfully

Avoid combining unrelated changes into a single pull request.

---

# Reporting Bugs

Include

* operating system
* compiler
* build configuration
* command executed
* expected behaviour
* actual behaviour
* error output

The more information included, the easier the issue is to reproduce.

---

# Feature Requests

Before requesting a feature, consider whether it fits the project's goals.

Good examples

* new archive formats
* performance improvements
* registry improvements
* better diagnostics
* bug fixes

Less suitable examples

* binary package management
* package compilation
* dependency resolution
* IDE integration

Those are intentionally outside the scope of **src**.

---

# Documentation

Documentation improvements are always welcome.

If you change

* commands
* manifests
* registry behaviour
* architecture
* installation flow

please update the relevant documentation.

---

# Testing

Before submitting changes

* Build successfully.
* Verify the modified functionality.
* Ensure existing commands continue to work.

Typical manual test sequence

```bash id="nlnrq5"
src registry update
src search raylib
src info raylib
src install raylib
src list
src remove raylib
```

---

# Registry Changes

Package manifests do **not** belong in this repository.

Registry changes should be made in the separate **src-registry** repository using **src-init**.

Typical workflow

```text id="em8jj7"
GitHub Repository
        │
        ▼
src-init create
        │
        ▼
Manifest
        │
        ▼
src-init registry build
        │
        ▼
Commit to src-registry
```

---

# Project Structure

```text id="kjlwm3"
src/
├── include/
├── src/
├── docs/
├── tests/
├── CMakeLists.txt
├── README.md
└── CONTRIBUTING.md
```

Keep related code together and avoid introducing unnecessary directories.

---

# Design Philosophy

Every component should have a single responsibility.

Example

```text id="hykz4r"
RegistryManager
        │
Synchronize registry

Parser
        │
Read manifests

Downloader
        │
Download files

Extractor
        │
Extract archives

PackageDownloader
        │
Install packages
```

Keeping responsibilities isolated makes the project easier to maintain and extend.

---

# License

By contributing to this project, you agree that your contributions will be licensed under the same license as **src**.

---

# Thank You

Every contribution, whether it's a bug report, documentation improvement, feature, or code change, helps make **src** better.

Thank you for helping improve the project.
