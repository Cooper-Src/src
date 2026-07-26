[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
# src

A lightweight source retrieval tool.

`src` is a command-line application that downloads and organizes source code. Unlike traditional package managers, `src` does **not** build, install, or modify your projects—it simply retrieves the source code and stores it in a central location.

## Philosophy

`src` follows a simple principle:

> Do one thing well.

Its responsibility is to retrieve source code. Building, compiling, and integrating that source into your project is left to your existing build system.

## Features

* Install packages from the src registry.
* Clone source code directly from Git repositories.
* Custom `.src` package manifest format.
* List installed packages.
* Update installed packages.
* Remove installed packages.
* Store repositories in a central package cache.
* Lightweight and fast.
* No build system integration.
* No dependency on a specific compiler.

## Current Status

`src` is currently in active development.

Implemented features:

* pull <package>
* pull <git-url>
* list
* update
* remove
* help
* version
* Custom `.src` manifest parser
* `.src` package manifests
* Package registry
* `list`
* `remove`
* `update`
* `pull <package>`

Planned features:

* `list`
* `remove`
* `update`
* `.src` package manifests
* Package registry
* `pull <package>`

## Examples

Install from the registry:

```bash
src pull raylib
```

Clone directly from Git:

```bash
src pull https://github.com/raysan5/raylib.git
```

List installed packages:

```bash
src list
```

Update a package:

```bash
src update raylib
```

Remove a package:

```bash
src remove raylib
```

## Project Goals

* Keep the command-line interface simple.
* Never force a build system.
* Store source code in a predictable location.
* Make downloading source code as easy as possible.

### v0.1

- Project foundation
- Command system
- Git repository cloning
- Local package storage

### v0.2

- Package registry
- `.src` manifest parser
- Pull by package name
- Package listing
- Package updating
- Package removal

### v0.3

- Registry search
- Dependency resolution
- Package metadata
- Improved manifest validation

### Future

- Cross-platform support
- Community registries
- Multiple registry support

## Contributing

Contributions, bug reports, feature requests, and suggestions are welcome as the project evolves.

## License

## Architecture

src is composed of several small components:

- Command system
- Registry
- Manifest parser
- Git interface
- Package manifest model
- Path management

Each component has a single responsibility, making the project easy to extend and maintain.

This project is licensed under the MIT License.
