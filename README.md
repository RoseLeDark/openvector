# openvector

### Common Features

### Building

Requirements:

  * Meson 0.49 or newer
  * Ninja 1.8.2 or newer
  * A C compiler
  * A C++ compiler

#### To build from command line, go into one of the project directories, then:

To initialize the builder:

    meson build

To build the project from then on:

    ninja -C build

To run the tests:

    ninja -C build test

To run the tests with full "google test" reporting:

    ./build/run_tests

All build files will be put in the `build` subdir, which is included in `.gitignore`.
