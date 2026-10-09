# Sorted bag using dynamic arrays

A sorted multiset of integers stored as parallel arrays of unique elements and occurrence counts. A caller-supplied relation controls ascending or descending ordering.

## How it works

`SortedBag` owns the arrays and resizes them as needed. `SortedBagIterator` traverses values in relation order and repeats each value according to its frequency. `ShortTest` and `ExtendedTest` exercise the public API, including removal of all occurrences.

## Architecture

Public bag API → storage implementation → iterator; test drivers verify the same contract.

## Build and run

Requires CMake 3.16 or newer and a compiler supporting the C++ standard specified in `CMakeLists.txt`.

Run these commands from this project folder:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/A1_ADS
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

