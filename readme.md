# LibGfx

A simple and minimal graphics library,
made as final project of the *Advanced Graphics* course for the Master in Computer Game Development.

It provides `constexpr` structs for handling vectors, quaternions, general rotations and 3x3 matrices.

I have to admit, this project is in a very incomplete state.
Sadly, I had to implement the bare minimum to satisfy a tight schedule. \
Notable additions would be:
- A Transform class, that would combine rotation, translation, and scaling
- 4x4 matrix export for graphics libraries interop
- A proper graphical test (which would require additional knowledge on graphical APIs)

## Build and Test
This is mostly an `inline constexpr` library, so there's very little to compile ahead of time
(I made a single `.cpp` file for stdout, just to have something to compile and produce a binary to link).

The project provides a single [`test.cpp`](tests/test.cpp) source,
made up of unit tests for the library. \
You can also use it to test the compilation and linkage of a demo project.

The project uses CMake as its main cross-platform build system.
You can easily use the `cmake` command for building and running tests if you feel confident with it,
or you can use other methods that wrap its functionalities.

### POSIX
I provide a `Makefile` for POSIX environments
(tested on macOS, but it should work on Linux and MSYS/MinGW).

It just wraps the CMake commands into a more intuitive interface.

#### Usage
- `make lib` compiles the dynamic library
- `make test` compiles the library and runs the unit tests
- `make clean` cleans the build

### Windows
If you just want an IDE to do the work, you can count on VS support for CMake
(and others, I suppose, like Rider).


Here's the [official guide](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170),
but you should be able to simply open it as a directory and VS should automatically do its magic.
