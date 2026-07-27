# Package Layout

Packages are stored inside the local package cache.

Windows:

```
%LOCALAPPDATA%\src\
```

Layout:

```
src/
├── packages/
├── registry/
└── temp/
```

## packages

Contains extracted source code.

Example:

```
packages/
    raylib/
    glfw/
    glm/
```

## registry

Contains `.src` manifests.

## temp

Temporary download archives.