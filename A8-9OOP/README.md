# Tutorial library with a Qt interface

A Qt desktop interface for a programming-tutorial library, watchlists, and undo/redo actions.

## How it works

`GUI` presents controls and lists. `Service/Service` coordinates operations and `Service/Action` represents reversible changes. Domain validators check tutorial data. Repository subclasses load/save tutorials and export watchlists to CSV or HTML. Qt Widgets is the presentation dependency.

## Architecture

User input → UI/window → service → repository → domain records/storage. Qt applications broadcast changes through signals so dependent windows refresh.

Source folders: `Domain/`, `Repository/`, `Service/`.

## Build and run

Requires CMake 3.16 or newer and a compiler supporting the C++ standard specified in `CMakeLists.txt`. Install Qt 6 Core, Gui and Widgets from the same compiler toolchain.

Run these commands from this project folder:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="/path/to/Qt/6.x/compiler-kit"
cmake --build build
./build/A8_9OOP
```

On Windows the executable has a `.exe` extension; multi-configuration generators may place it under `build/Debug/`. Run from the project folder so bundled text files can be located. Make Qt DLLs/plugins available on PATH or deploy the executable with `windeployqt`.

## Verification

Checked on 2026-10-09: build: passed, startup: passed.

The GUI was started offscreen for a smoke check. Full interaction workflows were not automated.

## Refinements

- Made CMake portable; removed local Qt paths/deployment assumptions and unused dependencies.

