[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# src

A lightweight source code retrieval tool.

`src` is a command-line application that downloads and organizes source code from a package registry or directly from Git repositories.

Unlike traditional package managers, **src never builds, installs, compiles, or manages dependencies.** It simply retrieves source code and stores it in a predictable location for you to use however you like.

---

# Philosophy

`src` follows one simple idea:

> Retrieve source code. Nothing more.

There is no build system integration, compiler configuration, dependency resolution, or package installation.

If you need a library, `src` gives you the source tree. What you do with it is entirely up to you.

---

# Features

- Download packages from the src registry
- Download directly from GitHub repositories
- Automatic default branch detection
- Download GitHub source archives (no Git required)
- Fast download progress display
- Archive extraction progress
- Automatic cleanup of `.git*` files after extraction
- Custom `.src` package manifests
- Search the registry
- Display package information
- List installed packages
- Update one package or every installed package
- Remove installed packages
- Central package cache
- Lightweight with no external build system integration

---

# Commands

| Command | Description |
|---------|-------------|
| `src pull <package>` | Download a package from the registry |
| `src pull <git-url>` | Download directly from a GitHub repository |
| `src search <query>` | Search the registry |
| `src info <package>` | Show package information |
| `src list` | List installed packages |
| `src update` | Update every installed package |
| `src update <package>` | Update a single package |
| `src remove <package>` | Remove a package |
| `src help` | Show help |
| `src version` | Show version information |

---

# Examples

Download from the registry

```bash
src pull raylib
```

Download directly from GitHub

```bash
src pull https://github.com/raysan5/raylib.git
```

Search the registry

```bash
src search ray
```

Display package information

```bash
src info raylib
```

List installed packages

```bash
src list
```

Update every package

```bash
src update
```

Update one package

```bash
src update raylib
```

Remove a package

```bash
src remove raylib
```

---

# Project Goals

- Keep the interface simple
- Never require Git to download packages
- Never require a specific compiler
- Never force a build system
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
