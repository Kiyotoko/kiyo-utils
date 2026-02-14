# Set minimum CMake version (supports modern features like FetchContent)
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
 
project(kiyo-utils
    LANGUAGES C    
    VERSION 0.1.0
)

# Global C++ standard (applies to all subprojects by default)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)  # Enforce the standard
set(CMAKE_C_EXTENSIONS OFF)        # Disable non-standard extensions (e.g., GNU++17)

enable_testing()

# Include subprojects (order matters for dependencies!)
add_subdirectory(kiyo-collections)  # Library: Must come before app/tests (which depend on it)
add_subdirectory(tests)       # Tests: Depends on math_utils
