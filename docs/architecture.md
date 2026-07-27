# Architecture

`src` is designed around small, focused components. Each component has a single responsibility.

## Installation Pipeline

```
Command
    │
    ▼
PackageDownloader
    │
    ├── GitHubProvider
    ├── Downloader
    ├── Extractor
    └── Cleanup
```

## Components

### Command

Implements every CLI command.

Examples:

- pull
- update
- remove
- search
- info
- list

---

### Registry

Stores package manifests.

The registry is simply a collection of `.src` files.

---

### Manifest Parser

Reads `.src` files into `PackageManifest` objects.

---

### GitHub Provider

Communicates with the GitHub API to determine:

- repository owner
- repository name
- default branch
- archive download URL

---

### Downloader

Downloads archives while displaying progress.

---

### Extractor

Extracts ZIP archives.

The extractor never performs cleanup.

---

### Cleanup

Removes repository metadata after extraction.

Currently removes every file or directory beginning with `.git`.

---

### Paths

Provides platform-specific filesystem locations.

All path logic is centralized here.