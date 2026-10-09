# Patient management desktop application

A Qt desktop application for organizing patient records and presenting doctor-specific views.

## How it works

Domain types model patients and doctors. Repository functions load/save patient and doctor records. The service coordinates record changes and emits notifications. The main window, doctor windows and add-patient dialog provide the interface.

## Architecture

User input → UI/window → service → repository → domain records/storage. Qt applications broadcast changes through signals so dependent windows refresh.

## Build and run

Requires CMake 3.16 or newer and a compiler supporting the C++ standard specified in `CMakeLists.txt`. Install Qt 6 Core, Gui and Widgets from the same compiler toolchain.

Run these commands from this project folder:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="/path/to/Qt/6.x/compiler-kit"
cmake --build build
./build/PatientManagement
```

On Windows the executable has a `.exe` extension; multi-configuration generators may place it under `build/Debug/`. Run from the project folder so bundled text files can be located. Make Qt DLLs/plugins available on PATH or deploy the executable with `windeployqt`.

## Verification

Checked on 2026-10-09: build: passed, startup: passed.

The GUI was started offscreen for a smoke check. Full interaction workflows were not automated.

## Refinements

- Made CMake portable; removed local Qt paths/deployment assumptions and unused dependencies.

