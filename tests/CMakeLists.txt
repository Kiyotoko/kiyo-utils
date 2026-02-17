include(FetchContent)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.5.2
)
FetchContent_MakeAvailable(unity)

# Define the test executable
add_executable(test_b_tree_map src/test_b_tree_map.c)
add_executable(test_b_tree_set src/test_b_tree_set.c)
add_executable(test_linked_list src/test_linked_list.c)
add_executable(test_vec src/test_vec.c)
 
target_link_libraries(test_b_tree_map
    PRIVATE
        kiyo-collections
        unity
)
target_link_libraries(test_b_tree_set
    PRIVATE
        kiyo-collections
        unity
)
target_link_libraries(test_linked_list
    PRIVATE
        kiyo-collections
        unity
)
target_link_libraries(test_vec
    PRIVATE
        kiyo-collections
        unity
)

add_test(NAME test_b_tree_map COMMAND test_b_tree_map)
add_test(NAME test_b_tree_set COMMAND test_b_tree_set)
add_test(NAME test_linked_list COMMAND test_linked_list)
add_test(NAME test_vec COMMAND test_vec)
