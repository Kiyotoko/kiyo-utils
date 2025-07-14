#include "src/assertations.h"
#include "src/array_list.h"
#include "src/linked_list.h"
#include "src/list.h"
#include "src/binary_tree.h"
#include "src/tree_set.h"

void array_list_test() {
    ArrayList* list = array_list_create(sizeof(int));
    assert_equals(0, array_list_len(list));
    assert_true(array_list_is_empty(list));
    for (int i = 0; i < 64; i++) {
        array_list_add(list, &i);
    }
    assert_equals(64, array_list_len(list));
    for (int i = 0; i < array_list_len(list); i++) {
        int a;
        assert_false_with(array_list_get(list, i, &a), "Expected array list could get element");
        assert_equals(i, a);
    }
    assert_false_with(array_list_is_empty(list), "Expected array list is not empty");
    array_list_clear(list);
    assert_true_with(array_list_is_empty(list), "Expected array list is empty");
    array_list_destroy(list);

    succeed_with("ArrayList run successfully");
}

int compere(void* left, void* right) {
    return *(int*)right - *(int*)left;
}

void binary_tree_test() {
    BinaryTree* tree = binary_tree_create(sizeof(int), &compere);
    assert_equals(0, binary_tree_height(tree));
    for (int i = 0; i<32; i++) {
        binary_tree_add(tree, &i);
    }
    assert_equals(6, binary_tree_height(tree));
    binary_tree_destroy(tree);

    succeed_with("BinaryTree run successfully");
}

void linked_list_test() {
    LinkedList* created = linked_list_create(sizeof(int));
    for (int i = 0; i < 16; i++) {
        linked_list_add(created, &i);
    }
    linked_list_destroy(created);

    succeed_with("LinkedList run successfully");
}

void list_test() {
    List* list = list_create(sizeof(int));
    int value;
    for (int i = 0; i < 3; i++) {
        list_add(list, &i);
        assert_false_with(list_last(list, &value), "Expected list last succeeds");
        assert_equals_with(i, value, "Expected added list element is last");
    }
    assert_success_with(list_first(list, &value), "Expected list first succeeds");
    assert_equals(0, value);
    assert_success_with(list_last(list, &value), "Expected list last succeeds");
    assert_equals_with(2, value, "Expected last element is 2");
    size_t index = 2;
    assert_success(list_get(list, index, &value));
    assert_equals_with(2, value, "Expected element at index 2 is 2");
    assert_success_with(list_remove_obj(list, &value, &index), "Expected list remove obj succeeds");
    assert_equals_with(2, index, "Expected removed element is 2");
    assert_success_with(list_last(list, &value), "Expected list last succeeds");
    assert_equals(1, value);
    assert_failure_with(list_remove(list, index, &value), "Expected list out of bounds");
    for (int i = list_len(list)-1; i >= 0; i--) {
        assert_success(list_remove(list, i, &value));
        assert_equals(i, value);
    }

    list_destroy(list);

    succeed_with("List run successfully");
}

void tree_set_test() {
    TreeSet* set = tree_set_create(sizeof(int), &compere);
    assert_equals(0, tree_set_size(set));
    int i = 0;
    for (; i < 3; i++) {
        assert_equals(EXIT_SUCCESS, tree_set_add(set, &i));
    }
    assert_equals(3, tree_set_size(set));
    i = 1;
    assert_true(tree_set_contains(set, &i));
    assert_equals_with(EXIT_UNCHANGED, tree_set_add(set, &(i)), "Expected tree unchanged");
    i = 10;
    assert_false_with(tree_set_contains(set, &i), "Expected tree does not contain element 10");
    tree_set_destroy(set);

    succeed_with("TreeSet run successfully");
}

int main() {
    array_list_test();
    binary_tree_test();
    linked_list_test();
    list_test();
    tree_set_test();

    return 0;
}
