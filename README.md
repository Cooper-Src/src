# src

A lightweight source retrieval tool.

`src` is a command-line application that downloads and organizes source code. Unlike traditional package managers, `src` does **not** build, install, or modify your projects—it simply retrieves the source code and stores it in a central location.

## Philosophy

`src` follows a simple principle:

> Do one thing well.

Its responsibility is to retrieve source code. Building, compiling, and integrating that source into your project is left to your existing build system.

## Features

* Pull source code directly from Git repositories.
* Store repositories in a central package cache.
* Lightweight and fast.
* No build system integration.
* No dependency on a specific compiler.
* Designed to grow with a future package registry.

## Current Status

`src` is currently in active development.

Implemented features:

* `pull <git-url>`
* `help`
* `version`

Planned features:

* `list`
* `remove`
* `update`
* `.src` package manifests
* Package registry
* `pull <package>`

## Example

Pull a repository directly from GitHub:

```bash
src pull https://github.com/raysan5/raylib.git
```

Repositories are currently stored under:

```text
%LOCALAPPDATA%\src\packages\
```

Example:

```text
C:\Users\<username>\AppData\Local\src\packages\raylib\
```

## Project Goals

* Keep the command-line interface simple.
* Never force a build system.
* Store source code in a predictable location.
* Make downloading source code as easy as possible.

## Roadmap

### v0.1

* Project foundation
* Command system
* Git repository cloning
* Local package storage

### v0.2

* Package registry
* `.src` manifest parser
* Pull by package name

### Future

* Cross-platform support
* Community package registry
* Improved package discovery

## Contributing

Contributions, bug reports, feature requests, and suggestions are welcome as the project evolves.

## License

This project is licensed under the MIT License.
