# Sorted bag using a doubly linked list

A sorted integer multiset in which each linked node stores a value and its occurrence count.

## How it works

`SortedBag` maintains head/tail pointers and the total size. Nodes link both forward and backward; insertion finds the correct position under the supplied relation. The iterator keeps a node and an occurrence offset. Separate short and extended suites verify behavior.

## Architecture

Public bag API → storage implementation → iterator; test drivers verify the same contract.

## Build and run

Requires CMake 3.16 or newer and a compiler supporting the C++ standard specified in `CMakeLists.txt`.

Run these commands from this project folder:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/A2_ADS
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

