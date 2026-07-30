# Commands

This document describes every command currently supported by **src**.

---

# Overview

```
src install
src remove
src list
src search
src info
src registry update
src update
src help
src version
```

---

# install

Installs a package from the local registry.

## Syntax

```bash
src install <package>
```

Example

```bash
src install raylib
```

Installation process

```
Load manifest
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

Packages are installed from upstream source archives.

---

# remove

Removes an installed package.

## Syntax

```bash
src remove <package>
```

Example

```bash
src remove raylib
```

Only the installed package is removed.

The registry remains unchanged.

---

# list

Displays all installed packages.

## Syntax

```bash
src list
```

Example

```
Installed Packages

fmt
glfw
raylib
zlib
```

---

# search

Searches the local registry.

## Syntax

```bash
src search <query>
```

Example

```bash
src search ray
```

Possible output

```
raylib
```

Searching only uses the local registry.

No network requests are made.

---

# info

Displays information about a package.

## Syntax

```bash
src info <package>
```

Example

```bash
src info raylib
```

Example output

```
Name        : raylib
Version     : 6.0

Description :
A simple and easy-to-use library to enjoy videogames programming

License     : Zlib

Homepage
https://www.raylib.com

Source

Type
archive

URL
https://github.com/raysan5/raylib/archive/refs/tags/6.0.zip
```

---

# registry update

Synchronizes the local registry.

## Syntax

```bash
src registry update
```

Example output

```
Pulling registry index

Registry version : 1

Updating manifests...

Registry synchronized successfully.

Manifests checked : 136
Updated           : 136
Failed            : 0
```

The registry is downloaded from the configured registry source.

No installed packages are modified.

---

# update

Updates installed packages.

## Syntax

```bash
src update
```

Typical workflow

```
Update registry
        │
        ▼
Compare versions
        │
        ▼
Download newer archives
        │
        ▼
Replace installed packages
```

Unlike

```
src registry update
```

this command affects installed packages.

---

# help

Displays command usage.

## Syntax

```bash
src help
```

---

# version

Displays the current src version.

## Syntax

```bash
src version
```

Example

```
src v0.3.0
```

---

# Exit Codes

| Code | Meaning           |
| ---- | ----------------- |
| 0    | Success           |
| 1    | Invalid arguments |
| 2    | Package not found |
| 3    | Download failed   |
| 4    | Extraction failed |
| 5    | Registry error    |

---

# Typical Usage

Install a package

```bash
src registry update
src install raylib
```

Search before installing

```bash
src search glfw
src info glfw
src install glfw
```

Remove a package

```bash
src remove glfw
```

Update installed packages

```bash
src update
```

---

# Notes

* `src install` installs source archives only.
* `src registry update` only synchronizes the local registry.
* `src update` updates installed packages.
* Registry maintenance is performed using **src-init**.
