include(FetchContent)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.5.2
)
FetchContent_MakeAvailable(unity)

# Define the test executable
add_executable(list_tests src/test_lists.c)
add_executable(trees_tests src/test_trees.c)
 
target_link_libraries(list_tests
    PRIVATE
        kiyo-collections
        unity
)
target_link_libraries(trees_tests
    PRIVATE
        kiyo-collections
        unity
)

add_test(NAME list_tests COMMAND list_tests)
add_test(NAME trees_tests COMMAND trees_tests)
