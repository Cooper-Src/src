# src Manifest Specification v1

Version: 1.0

## Overview

A `.src` file is a package definition used by `src` to retrieve source code.

Each manifest describes a single package and contains the information required to download it.

The current implementation only supports Git repositories, but the format is designed to support additional source types in the future.

---

# File Extension

```
.src
```

Example:

```
raylib.src
```

---

# Manifest Format

The `.src` format uses a simple INI-inspired syntax.

Values are stored as key/value pairs.

Sections are declared using square brackets.

Example:

```ini
name = raylib
version = 5.6

[source]
type = git
url = https://github.com/raysan5/raylib.git
branch = master
```

---

# Required Fields

The following fields are required.

```
name
version

[source]
type
url
```

If any required field is missing, the manifest is considered invalid.

---

# Optional Fields

The following fields are optional.

```
description

[source]
branch

[license]
name

[homepage]
url
```

Future versions may introduce additional optional sections.

---

# Supported Sections

## Root

| Key | Required | Description |
|-----|----------|-------------|
| name | Yes | Package name |
| version | Yes | Package version |
| description | No | Short package description |

---

## [source]

Defines where the source code is retrieved from.

| Key | Required | Description |
|-----|----------|-------------|
| type | Yes | Source type |
| url | Yes | Repository or download URL |
| branch | No | Branch to retrieve |

Currently supported source types:

```
git
```

---

## [license]

| Key | Required | Description |
|-----|----------|-------------|
| name | No | Package license |

Example:

```ini
[license]
name = zlib
```

---

## [homepage]

| Key | Required | Description |
|-----|----------|-------------|
| url | No | Project homepage |

Example:

```ini
[homepage]
url = https://www.raylib.com
```

---

# Example Manifest

```ini
name = raylib
version = 5.6
description = A simple and easy-to-use library to learn game programming.

[source]
type = git
url = https://github.com/raysan5/raylib.git
branch = master

[license]
name = zlib

[homepage]
url = https://www.raylib.com
```

---

# Registry Layout

Package manifests should be stored using the package name.

```
registry/
├── raylib.src
├── glfw.src
├── fmt.src
└── imgui.src
```

The filename should match the package name.

Example:

```
raylib.src
```

contains

```ini
name = raylib
```

---

# Parser Requirements

A parser should:

- Ignore blank lines.
- Ignore leading and trailing whitespace.
- Ignore unknown sections.
- Ignore unknown keys.
- Validate all required fields.
- Reject malformed manifests.

---

# Future Compatibility

The format is intentionally extensible.

Future versions may introduce sections such as:

```
[dependencies]
[author]
[build]
[platform]
```

Older versions of `src` should ignore sections they do not recognize whenever possible.

---

# Design Goals

- Human readable
- Easy to edit
- Easy to parse
- Lightweight
- Extensible
- Versionable

---

Copyright © Cooper-Src

This specification defines Version 1.0 of the `.src` manifest format.