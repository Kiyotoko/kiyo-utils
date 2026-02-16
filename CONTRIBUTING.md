# Contributing

## Configure with CMake

```sh
mkdir build && cd build  # Create build directory (out-of-source build)
cmake ..  # Generate build files (Makefiles, etc.)
```

## Build

```sh
cmake --build .  # Build all targets (kiyo-collections and tests)
# Or build a specific target:
cmake --build . --target kiyo-collections  # Only build the app
```

## Run Tests

```sh
ctest  # Run all tests (from the build directory)
```

## Check for Memleaks

```sh
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./tests/your-test
```
