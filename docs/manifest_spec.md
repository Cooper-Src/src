# Manifest Specification

This document defines the `.src` package manifest format used by **src**.

Every package available through a registry is described by a single manifest file.

---

# Overview

A manifest provides all the information required for `src` to locate, download, and install a package.

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

# File Extension

All manifests use the

```
.src
```

extension.

Example

```
raylib.src
```

---

# Encoding

Manifest files must be

* UTF-8
* Plain text
* Human readable

---

# Root Fields

## name

Package name.

```ini
name = raylib
```

Requirements

* Required
* Unique within a registry
* Case-sensitive

---

## version

Current upstream version.

```ini
version = 6.0
```

Examples

```
6.0
v1.8.2
2026.07
```

---

## description

Short package description.

```ini
description = A simple and easy-to-use library
```

Requirements

* Required
* Single line

---

# Source Section

```
[source]
```

Defines where the package source is downloaded.

---

## type

Current supported values

```ini
type = archive
```

Supported types

| Type    | Description                          |
| ------- | ------------------------------------ |
| archive | Download a compressed source archive |

---

## url

Archive download URL.

```ini
url = https://github.com/raysan5/raylib/archive/refs/tags/6.0.zip
```

Requirements

* Required
* HTTPS recommended

---

## format

Archive format.

```ini
format = zip
```

Currently supported

```
zip
```

Future versions may support

* tar.gz
* tar.xz
* 7z

---

# License Section

```
[license]
```

---

## name

License identifier.

```ini
name = MIT
```

Recommended values

```
MIT
Apache-2.0
BSD-3-Clause
GPL-3.0
Zlib
```

SPDX identifiers are recommended whenever possible.

---

# Homepage Section

```
[homepage]
```

---

## url

Project homepage.

```ini
url = https://www.raylib.com
```

Requirements

* Required
* Valid URL

---

# Complete Example

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

# Validation Rules

A manifest is considered valid when

* every required field exists
* the source section exists
* the license section exists
* the homepage section exists
* the source URL is valid
* the archive format is supported

Invalid manifests are rejected during installation.

---

# Installation Process

The manifest is consumed in the following order.

```text
Load manifest
        │
        ▼
Validate fields
        │
        ▼
Download archive
        │
        ▼
Extract archive
        │
        ▼
Install package
```

---

# Supported Archive Formats

| Format | Supported |
| ------ | :-------: |
| zip    |     ✓     |
| tar.gz |  Planned  |
| tar.xz |  Planned  |
| 7z     |  Planned  |

---

# Naming Guidelines

Package names should match the upstream project.

Good

```
raylib
fmt
glfw
```

Avoid

```
raylib-library
fmt-library
glfw-source
```

unless required to avoid conflicts.

---

# Version Guidelines

Always use the upstream version.

Good

```
6.0
v1.3.2
```

Avoid

```
latest
master
stable
```

Versions should uniquely identify a release.

---

# Description Guidelines

Descriptions should be short and informative.

Good

```
Modern C++ formatting library.
```

Avoid

```
This library was created many years ago...
```

---

# Registry Relationship

Every manifest belongs to a registry.

Example

```text
src-registry/
├── index.json
└── manifests/
    ├── raylib.src
    ├── fmt.src
    ├── glfw.src
    └── ...
```

`index.json` lists every manifest available in the registry.

---

# Compatibility

Current manifest version

```
Version 1
```

Future versions of `src` aim to remain backward compatible with existing manifests whenever practical.

---

# Future Extensions

Possible future additions include

```ini
[dependencies]
```

```ini
[authors]
```

```ini
[documentation]
```

```ini
checksum = ...
```

```ini
sha256 = ...
```

These additions are expected to remain compatible with Version 1 manifests.

---

# Summary

A `.src` manifest is intentionally simple.

It describes

* what the package is
* where to download it
* what archive format it uses
* its license
* its homepage

No build instructions, dependency information, or platform-specific configuration are included, keeping manifests lightweight and easy to maintain.
