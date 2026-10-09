# Tutorial manager with a custom dynamic array

A console tutorial catalogue with administrator operations and a user watchlist.

## How it works

`Tutorial` defines records; `DynamicArray` supplies custom storage. `Repository` owns catalogue data, `Watchlist` owns selections, `Service` implements operations, and `UI` handles input. `Test` contains domain, repository, service and watchlist checks. Data is in memory for this version.

## Architecture

User input → UI → service → repository → domain records/storage.

## Build and run

Requires CMake 3.16 or newer and a compiler supporting the C++ standard specified in `CMakeLists.txt`.

Run these commands from this project folder:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/Assignment4OOP
```

On Windows the executable has a `.exe` extension; multi-configuration generators may place it under `build/Debug/`. Run from the project folder so bundled text files can be located.

## Tests

```sh
./build/Assignment4OOP --test
```

This runs existing tests and exits before starting the menu.

## Verification

Checked on 2026-10-09: build: passed, tests: passed.

## Refinements

- Made CMake portable; removed local Qt paths/deployment assumptions and unused dependencies.
- Added --test to run the existing domain/service tests without entering the menu.

