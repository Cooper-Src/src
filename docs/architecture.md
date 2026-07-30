# Architecture

This document describes the internal architecture of **src**, how packages are installed, and how the different components work together.

---

# Overview

`src` is a lightweight, source-first package manager.

Its primary responsibilities are:

* Synchronize package registries
* Read package manifests
* Download source archives
* Extract packages
* Manage installed source packages

Unlike traditional package managers, **src does not build or compile packages**.

---

# High-Level Architecture

```text
             Registry
                │
                ▼
        RegistryManager
                │
                ▼
       Manifest Parser
                │
                ▼
      PackageDownloader
                │
        Download Archive
                │
                ▼
          ZIP Extractor
                │
                ▼
      Installed Package
```

---

# Project Structure

```text
src/
├── include/
│   ├── cleanup.hpp
│   ├── command.hpp
│   ├── downloader.hpp
│   ├── extractor.hpp
│   ├── manifest.hpp
│   ├── package_downloader.hpp
│   ├── parser.hpp
│   ├── paths.hpp
│   ├── registry_manager.hpp
│   └── ...
│
├── src/
│   ├── cleanup.cpp
│   ├── command.cpp
│   ├── downloader.cpp
│   ├── extractor.cpp
│   ├── package_downloader.cpp
│   ├── parser.cpp
│   ├── registry_manager.cpp
│   └── ...
│
├── docs/
└── tests/
```

---

# Components

## Command

The command dispatcher is the application's entry point.

Responsibilities

* Parse command-line arguments
* Execute commands
* Display help
* Return exit codes

---

## RegistryManager

Responsible for synchronizing the local registry.

Responsibilities

* Download `index.json`
* Download package manifests
* Store manifests locally

The registry manager never installs packages.

---

## Parser

Reads `.src` manifests from disk.

Responsibilities

* Parse manifests
* Validate required fields
* Produce a `PackageManifest`

Example

```text
raylib.src
        │
        ▼
PackageManifest
```

---

## PackageManifest

Represents a parsed package manifest.

Typical fields include

```text
name
version
description

sourceType
sourceUrl

license

homepage
```

This object is used throughout the installation process.

---

## Downloader

Downloads remote files.

Responsibilities

* HTTPS downloads
* Follow redirects
* Save archives

Unlike previous versions of `src`, the downloader no longer clones Git repositories.

---

## PackageDownloader

Coordinates package installation.

Responsibilities

* Download archives
* Extract packages
* Clean temporary files
* Install package contents

Workflow

```text
Manifest
    │
    ▼
Download archive
    │
    ▼
Extract archive
    │
    ▼
Cleanup
    │
    ▼
Installed package
```

---

## Extractor

Extracts downloaded archives.

Current support

```text
ZIP
```

Future versions may support

* tar.gz
* tar.xz
* 7z

---

## Cleanup

Removes unnecessary files after extraction.

Currently removes

* Git metadata
* `.git` directories
* `.gitignore`
* `.gitattributes`

This ensures installed packages only contain source files.

---

# Installation Flow

```text
src install raylib
        │
        ▼
Load manifest
        │
        ▼
Download archive
        │
        ▼
Extract archive
        │
        ▼
Cleanup
        │
        ▼
Install package
```

---

# Registry Flow

```text
GitHub Pages
        │
        ▼
index.json
        │
        ▼
RegistryManager
        │
        ▼
Download manifests
        │
        ▼
Local registry
```

---

# Data Flow

```text
Manifest
        │
        ▼
Parser
        │
        ▼
PackageManifest
        │
        ▼
PackageDownloader
        │
        ▼
Downloader
        │
        ▼
Extractor
        │
        ▼
Installed Package
```

---

# Package Installation Directory

Packages are installed into the user's local package directory.

Example

```text
%LOCALAPPDATA%/src/packages/

    raylib/
    fmt/
    glfw/
```

The registry is stored separately.

```text
%LOCALAPPDATA%/src/registry/
```

Keeping registry data separate from installed packages simplifies updates and maintenance.

---

# Design Principles

## Source First

`src` installs upstream source code exactly as published.

It does not create forks or mirrors.

---

## Archive Based

Packages are distributed as downloadable archives.

This removes the dependency on Git during installation and allows support for repositories that provide release archives.

---

## Lightweight

`src` intentionally does not include

* dependency resolution
* build systems
* package compilation
* binary distribution

These responsibilities belong to external tools.

---

## Modular

Each component has a single responsibility.

| Component         | Responsibility           |
| ----------------- | ------------------------ |
| RegistryManager   | Synchronize registries   |
| Parser            | Read manifests           |
| Downloader        | Download files           |
| Extractor         | Extract archives         |
| PackageDownloader | Install packages         |
| Cleanup           | Remove unnecessary files |

---

# Relationship with src-init

`src` and `src-init` are complementary projects.

### src-init

Creates package manifests.

Builds registry indexes.

Communicates with GitHub.

---

### src

Consumes manifests.

Downloads archives.

Installs source code.

---

The separation allows both projects to remain focused on their own responsibilities.

---

# Future Architecture

Planned improvements include

* Multiple registry support
* Package updates
* Archive verification
* Package checksums
* Additional archive formats
* Parallel downloads

These features can be added without changing the overall architecture because each subsystem is isolated behind a dedicated component.

---

# Summary

The architecture is intentionally simple.

```text
Registry
    │
RegistryManager
    │
Parser
    │
PackageManifest
    │
PackageDownloader
    │
Downloader
    │
Extractor
    │
Cleanup
    │
Installed Package
```

Each layer performs a single task, making `src` easy to maintain, test, and extend while remaining lightweight.
