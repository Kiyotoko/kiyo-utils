# Define the library target (STATIC = compiled into a .a/.lib file)
add_library(kiyo-collections STATIC
    src/array_list.c  # Source file
    src/binary_tree.c  # Source file
    src/linked_list.c  # Source file
    src/list.c  # Source file
    src/tree_set.c  # Source file
    include/kiyo-collections/array_list.h
    include/kiyo-collections/binary_tree.h
    include/kiyo-collections/functions.h
    include/kiyo-collections/linked_list.h
    include/kiyo-collections/tree_set.h
)

# Set include directories for the library and its dependents
target_include_directories(kiyo-collections
    PUBLIC  # "PUBLIC" propagates this include path to dependents (e.g., app/tests)
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  # Path during build
        $<INSTALL_INTERFACE:include>  # Path when installed (for find_package)
)

# Optional: Enable warnings for better code quality
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(kiyo-collections PRIVATE -Wall -Wextra -Wpedantic)
elseif(MSVC)
    target_compile_options(kiyo-collections PRIVATE /W4)
endif()

# Install the library and headers
install(TARGETS kiyo-collections
    EXPORT kiyo-collections  # Generates a cmake file for find_package
    ARCHIVE DESTINATION lib  # Install static library to <prefix>/lib
    LIBRARY DESTINATION lib  # Install shared library to <prefix>/lib (if using SHARED)
    RUNTIME DESTINATION bin  # Install DLLs to <prefix>/bin (Windows only)
    INCLUDES DESTINATION include  # Tells CMake where headers are installed
)
 
# Install public headers
install(DIRECTORY include/ DESTINATION include)
 
# Generate and install a CMake config file for find_package(math_utils)
install(EXPORT kiyo-collections
    FILE kiyo-collections.cmake
    NAMESPACE kiyo-collections
    DESTINATION lib/cmake/kiyo-collections  # Where find_package looks for config files
)
 
# Optional: Generate a Config.cmake file (simplifies find_package)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "kiyo-collections-config-version.cmake"
    VERSION 1.0.0
    COMPATIBILITY SameMajorVersion
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/kiyo-collections-config-version.cmake"
    DESTINATION lib/cmake/kiyo-collections
)