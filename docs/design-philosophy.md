# Design Philosophy

`src` exists to solve one problem:

> Download source code.

It intentionally does **not**:

- build projects
- compile libraries
- resolve dependencies
- manage toolchains
- replace existing build systems

Instead, `src` downloads clean source trees into a predictable location.

The project values simplicity over features.

Every new feature should support the goal of retrieving source code without expanding into a full package manager.