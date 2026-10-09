# Sorted bag using an array-based linked list

A sorted multiset implemented with indexed nodes in a fixed-capacity array rather than individually allocated linked nodes.

## How it works

Each node stores its value, frequency and next/previous indexes. A free-position chain allocates and reuses slots. `SortedBagIterator` walks indexes and emits repeated values. The capacity is 10,000 unique nodes; this is an explicit implementation limit.

## Architecture

Public bag API → storage implementation → iterator; test drivers verify the same contract.

## Build and run

Requires CMake 3.16 or newer and a compiler supporting the C++ standard specified in `CMakeLists.txt`.

Run these commands from this project folder:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/A3_ADS
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

