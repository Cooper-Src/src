# Registry

The registry is a collection of `.src` manifest files.

Example:

```
registry/
    raylib.src
    glfw.src
    glm.src
```

Each file describes exactly one package.

The registry does not store archives or binaries.

It only stores metadata required to locate source code.

## Searching

`src search`

Searches manifest filenames.

## Information

`src info`

Loads and parses the matching manifest.