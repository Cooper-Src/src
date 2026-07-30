# Source Types

Every package managed by **src** defines a source.

A source describes **where** a package is downloaded from and **how** `src` should retrieve it.

The source is defined in the `[source]` section of a package manifest.

---

# Overview

Example

```ini
[source]
type = archive
url = https://github.com/raysan5/raylib/archive/refs/tags/6.0.zip
format = zip
```

The source type determines how `src` downloads the package.

---

# Supported Source Types

| Type    |    Status   |
| ------- | :---------: |
| archive | ✓ Supported |

Additional source types may be added in future releases.

---

# Archive Source

The `archive` source downloads a compressed archive containing the package source code.

Example

```ini
[source]
type = archive
url = https://github.com/raysan5/raylib/archive/refs/tags/6.0.zip
format = zip
```

During installation

```text
Read manifest
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

No Git repository is cloned.

---

# Fields

## type

Identifies the source type.

```ini
type = archive
```

Currently, `archive` is the only supported value.

---

## url

The URL used to download the package.

Example

```ini
url = https://github.com/raysan5/raylib/archive/refs/tags/6.0.zip
```

Requirements

* Required
* Publicly accessible
* HTTPS recommended

---

## format

The archive format.

Example

```ini
format = zip
```

Currently supported

| Format | Supported |
| ------ | :-------: |
| zip    |     ✓     |

Planned

* tar.gz
* tar.xz
* 7z

---

# Download Process

The installer performs the following steps.

```text
Manifest
    │
    ▼
Read source
    │
    ▼
Download archive
    │
    ▼
Verify download
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

# Temporary Files

Archives are downloaded to a temporary location before extraction.

Example

```text
%TEMP%/
    raylib.zip
```

After extraction completes successfully, the temporary archive is deleted.

---

# Cleanup

Following extraction, `src` removes repository metadata that is not required for package installation.

Examples include

* `.git`
* `.gitignore`
* `.gitattributes`

This ensures installed packages contain only the upstream source files.

---

# Installation Directory

Packages are installed into

```text
%LOCALAPPDATA%/src/packages/
```

Example

```text
packages/

    raylib/
    fmt/
    glfw/
```

Each package receives its own directory.

---

# Why Archives?

Using release archives instead of Git repositories provides several advantages.

* Faster downloads
* Smaller downloads
* No Git dependency
* Deterministic releases
* Version-specific packages
* Simpler manifests

Archives also allow `src` to install packages from any source that exposes downloadable release archives.

---

# Best Practices

When creating manifests

Use release archives whenever available.

Prefer

```ini
url = https://github.com/owner/project/archive/refs/tags/v1.0.zip
```

instead of branch archives

```ini
url = https://github.com/owner/project/archive/refs/heads/master.zip
```

Release archives provide reproducible installations.

---

# Future Source Types

The source system is designed to be extensible.

Possible future source types include

```ini
[source]
type = archive
```

```ini
[source]
type = tarball
```

```ini
[source]
type = release
```

```ini
[source]
type = mirror
```

New source types will follow the same interface used by the current archive downloader.

---

# Summary

The source system is intentionally simple.

```text
Manifest
    │
    ▼
Source
    │
    ▼
Archive URL
    │
    ▼
Download
    │
    ▼
Extract
    │
    ▼
Installed package
```

This keeps package installation lightweight, reproducible, and independent of Git while allowing future expansion as new source types are introduced.
