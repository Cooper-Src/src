# Registry

A registry is a collection of package manifests that can be synchronized by **src**.

Registries allow packages to be discovered, searched, and installed without embedding package information inside the package manager itself.

The official registry is maintained using **src-init**.

---
 
# Overview

A registry consists of two components.

```text
src-registry/
├── index.json
└── manifests/
    ├── raylib.src
    ├── fmt.src
    ├── glfw.src
    └── ...
```

Every package is represented by a single `.src` manifest.

The registry index is generated automatically.

---

# Directory Structure

```
src-registry/
│
├── index.json
│
└── manifests/
    ├── CLI11.src
    ├── fmt.src
    ├── glfw.src
    ├── raylib.src
    ├── spdlog.src
    └── zlib.src
```

The `manifests` directory should be edited manually.

`index.json` should **never** be edited manually.

---

# index.json

The registry index tells `src` which manifests are available.

Example

```json
{
    "version": 1,
    "manifests": [
        "fmt.src",
        "glfw.src",
        "raylib.src",
        "spdlog.src",
        "zlib.src"
    ]
}
```

---

## version

```json
"version": 1
```

Represents the registry schema version.

It is **not** a package version.

---

## manifests

```json
"manifests": [
    "fmt.src",
    "glfw.src",
    "raylib.src"
]
```

A sorted list of every package manifest contained in the registry.

Each manifest appears exactly once.

---

# Local Registry

When the registry is updated it is downloaded into the local registry cache.

Example

```text
%LOCALAPPDATA%/src/registry/

    index.json

    manifests/
        raylib.src
        fmt.src
        glfw.src
```

The local registry is used for

* searching
* package information
* package installation

No network requests are required once the registry has been synchronized.

---

# Updating the Registry

Synchronize the registry.

```bash
src registry update
```

Example output

```text
Pulling registry index

Registry version : 1

Updating manifests...

Registry synchronized successfully.

Manifests checked : 136
Updated           : 136
Failed            : 0
```

---

# Synchronization Process

```text
GitHub Pages
      │
      ▼
index.json
      │
      ▼
Download index
      │
      ▼
Download manifests
      │
      ▼
Store locally
```

The registry manager downloads

1. `index.json`
2. every listed manifest

Only files listed in the registry index are synchronized.

---

# Package Installation

Installing a package uses the local registry.

```text
src install raylib
        │
        ▼
Local registry
        │
        ▼
raylib.src
        │
        ▼
Download archive
        │
        ▼
Extract package
```

The registry itself is never modified during installation.

---

# Registry Maintenance

Registries are maintained using **src-init**.

Typical workflow

```text
GitHub Repository
        │
        ▼
src-init create
        │
        ▼
package.src
        │
        ▼
src-registry/manifests
        │
        ▼
src-init registry build
        │
        ▼
index.json
        │
        ▼
Commit
        │
        ▼
GitHub Pages
```

---

# Best Practices

When maintaining a registry

* One manifest per package
* Use upstream package names
* Keep manifests alphabetically sorted
* Rebuild the registry after every change
* Commit both the new manifest and the updated `index.json`

---

# Hosting

A registry can be hosted on any static web server.

Examples

* GitHub Pages
* GitLab Pages
* Cloudflare Pages
* Static web hosting
* Local network servers

The only requirements are

* `index.json` must be publicly accessible
* the `manifests` directory must be publicly accessible

---

# Registry Versioning

Current registry version

```
Version 1
```

Future registry versions may introduce additional metadata while maintaining backward compatibility where practical.

---

# Future Improvements

Planned enhancements include

* Multiple registry support
* Registry priorities
* Mirror support
* Manifest verification
* Digital signatures
* Package checksums
* Incremental registry updates

---

# Summary

A registry is simply a collection of package manifests accompanied by a generated index.

```text
Registry
    │
    ├── index.json
    └── manifests/
            │
            ▼
       Package manifests
            │
            ▼
      src registry update
            │
            ▼
       Local registry cache
            │
            ▼
        Package installation
```

The registry remains lightweight, human-readable, and easy to maintain while allowing `src` to efficiently discover and install source packages.
