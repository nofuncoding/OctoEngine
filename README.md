# Octo Engine

## Overview

Octo Engine is a simple, lightweight, and easy-to-use game engine basiced on modern C++.

## Building

Currently, Octo Engine *only* supports Windows.

### Requirements

- [xmake](https://xmake.io/) 2.8.0 and newer
- One of the following compilers:
  - MSVC 19.28 and newer (provided with Visual Studio 16.8 and newer)
  - LLVM/Clang 12.0 and newer
  - GCC 11 and newer

### Step by step

1. Clone the repository: `git clone https://github.com/nofuncoding/OctoEngine.git`, or just download the source code and extract it.
2. Run the following commands:
```bash
xmake f # Configure the project up
xmake # Build the whole project
xmake run sandbox # Run the sandbox application to test the engine
```
3. You can find the built binaries in the `build` directory.

## License

Octo Engine is licensed under the MIT License. Check the [LICENSE](LICENSE) file for more information.

*Copyright (c) 2024 NoFun*
