# Tutorial library and file watchlists

A console application for managing programming tutorials and maintaining a user watchlist exported as CSV or HTML.

## How it works

`Domain/` defines tutorials, validation and parsing. `Repository/` stores tutorials and implements file-backed repositories and CSV/HTML watchlist exporters. `Service/` coordinates admin/user operations; `UI/` implements the menus. File records are loaded into memory and mutations are persisted by the file repository.

## Architecture

User input → UI → service → repository → domain records/storage.

Source folders: `Domain/`, `Repository/`, `Service/`, `UI/`.

## Build and run

Requires CMake 3.16 or newer and a compiler supporting the C++ standard specified in `CMakeLists.txt`.

Run these commands from this project folder:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/A67OOP
```

On Windows the executable has a `.exe` extension; multi-configuration generators may place it under `build/Debug/`. Run from the project folder so bundled text files can be located.

## Scope

Choose repository option 1 for file persistence, then CSV or HTML watchlist output. The menu label for the alternate repository says database, but the included implementation uses memory; no SQL backend is implemented.

## Verification

Checked on 2026-10-09: build: passed, runtime: passed.

## Refinements

- Made CMake portable; removed local Qt paths/deployment assumptions and unused dependencies.
- Loaded file records without rewriting and truncating the file during the read loop.

