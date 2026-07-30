[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# src

> The source-first package manager.

`src` is a lightweight package manager that installs source code instead of prebuilt binaries.

Packages are distributed through simple `.src` manifests stored in registries. Each manifest describes where the upstream source archive can be downloaded, allowing `src` to install projects directly from their original source.

---

# Features

* Install source packages from registries
* Archive-based package installation
* Lightweight manifest format
* Registry synchronization
* Cross-platform design
* Written in modern C++20
* Simple, predictable package format

---

# Philosophy

Unlike traditional package managers, **src** focuses exclusively on source code.

It intentionally does **not**

* distribute binaries
* build projects
* manage dependencies
* replace build systems

Instead, `src` provides a consistent way to obtain upstream source code.

---

# Installation

## Requirements

* CMake 3.20+
* C++20 compiler
* Visual Studio Build Tools (MSVC)
* vcpkg

Required libraries

* curl
* cJSON
* libarchive (or the extractor implementation used by your build)

Configure

```bash
cmake --preset default
```

Build

```bash
cmake --build build --config Release
```

---

# Quick Start

Update the registry

```bash
src registry update
```

Search for a package

```bash
src search raylib
```

Install a package

```bash
src install raylib
```

List installed packages

```bash
src list
```

Remove a package

```bash
src remove raylib
```

---

# Commands

## Registry

Synchronize the local registry.

```bash
src registry update
```

---

## Install

Install a package from the registry.

```bash
src install <package>
```

Example

```bash
src install raylib
```

---

## Remove

Remove an installed package.

```bash
src remove <package>
```

---

## List

Display installed packages.

```bash
src list
```

---

## Search

Search the local registry.

```bash
src search <package>
```

---

## Info

Display information about a package.

```bash
src info <package>
```

---

## Version

```bash
src version
```

---

## Help

```bash
src help
```

---

# Package Manifest

Every package is described using a simple `.src` manifest.

Example

```ini
name = raylib
version = 6.0
description = A simple and easy-to-use library to enjoy videogames programming

[source]
type = archive
url = https://github.com/raysan5/raylib/archive/refs/tags/6.0.zip
format = zip

[license]
name = Zlib

[homepage]
url = https://www.raylib.com
```

---

# Registry

A registry consists of two parts.

```
src-registry/
├── index.json
└── manifests/
    ├── raylib.src
    ├── fmt.src
    ├── glfw.src
    └── ...
```

`index.json` is generated automatically by **src-init**.

Package manifests are stored inside the `manifests` directory.

---

# Installation Process

```
src install raylib
        │
        ▼
Read registry
        │
        ▼
Load manifest
        │
        ▼
Download source archive
        │
        ▼
Extract archive
        │
        ▼
Install package
```

No Git repositories are cloned during installation.

---

# Registry Maintenance

Registries are maintained using **src-init**.

Typical workflow

```
GitHub Repository
        │
        ▼
src-init create
        │
        ▼
package.src
        │
        ▼
src-init registry build
        │
        ▼
index.json
        │
        ▼
GitHub Pages
        │
        ▼
src registry update
```

---

# Project Structure

```
src/
├── include/
├── src/
├── docs/
├── tests/
├── CMakeLists.txt
├── README.md
└── LICENSE
```

---

# Documentation

Additional documentation is available in the `docs` directory.

* Commands
* Architecture
* Manifest Specification
* Registry
* Source Types

---

# Roadmap

## Current

* Registry synchronization
* Archive-based installation
* Package removal
* Package listing
* Source archive extraction

## Planned

* Package updates
* Dependency support
* Multiple registries
* Registry validation
* Package verification
* Additional archive formats

---

# Contributing

Contributions are welcome.

Please read **CONTRIBUTING.md** before opening a pull request.

---

# Related Projects

### src-init

The official registry maintenance tool.

Responsibilities include

* manifest generation
* registry generation
* GitHub metadata retrieval
* authentication

---

# License

This project is licensed under the MIT License.
- Store source code in a predictable location
- Keep the codebase modular and easy to extend

---

# Architecture

`src` is built from small components with a single responsibility.

- Command system
- Registry
- Manifest parser
- GitHub provider
- Downloader
- Archive extractor
- Cleanup system
- Package downloader
- Path management
- Progress display

This modular architecture keeps the project easy to maintain and extend.

---

# Roadmap

## v0.1

- Project foundation
- Command system
- Git repository downloads
- Local package storage

## v0.2

- Registry support
- `.src` manifest parser
- Package installation
- Package listing
- Package removal
- Package updates

## v0.3

- Registry search
- Package information
- GitHub archive downloads
- Download progress
- Extraction progress
- Automatic `.git*` cleanup

## Planned

- Cross-platform support
- Multiple source providers (GitLab, Codeberg, etc.)
- Multiple registries
- Registry mirrors
- Config system
- Better update summaries

---

# Contributing

Bug reports, feature requests, and pull requests are welcome.

---

# License

This project is licensed under the MIT License.
