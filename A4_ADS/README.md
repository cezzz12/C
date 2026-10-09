# Sorted bag using a binary search tree

A sorted integer multiset with per-node frequencies and multiset intersection.

## How it works

`SortedBag` owns a binary search tree ordered by the supplied relation. Each node holds a value/frequency pair. The iterator traverses the tree in order. The tree is not self-balancing, so worst-case lookup/insertion can be linear.

## Architecture

Public bag API → storage implementation → iterator; test drivers verify the same contract.

## Build and run

Requires CMake 3.16 or newer and a compiler supporting the C++ standard specified in `CMakeLists.txt`.

Run these commands from this project folder:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/A4_ADS
```

On Windows the executable has a `.exe` extension; multi-configuration generators may place it under `build/Debug/`. Run from the project folder so bundled text files can be located.

## Tests

```sh
ctest --test-dir build --output-on-failure
```

The executable runs both the existing short and extended test suites. Use a Debug build so assertions are enabled.

## Verification

Checked on 2026-10-09: build: passed, tests: passed.

## Refinements

- Made CMake portable; removed local Qt paths/deployment assumptions and unused dependencies.
- Removed the Windows-only pause so the existing test executable can run unattended.

