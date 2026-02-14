#include <unity.h>
#include <stdlib.h>

#include "kiyo-collections/array_list.h"
#include "kiyo-collections/linked_list.h"
#include "kiyo-collections/list.h"

void setUp(void) {}
void tearDown(void) {}

void array_list_test() {
    ArrayList* list = array_list_create(sizeof(int));
    TEST_ASSERT(0 == array_list_len(list));
    TEST_ASSERT(array_list_is_empty(list));
    for (int i = 0; i < 64; i++) {
        array_list_add(list, &i);
    }
    TEST_ASSERT(64 == array_list_len(list));
    for (int i = 0; i < array_list_len(list); i++) {
        int a;
        TEST_ASSERT_MESSAGE(EXIT_SUCCESS == array_list_get(list, i, &a), "Expected array list could get element");
        TEST_ASSERT(i == a);
    }
    TEST_ASSERT_MESSAGE(!array_list_is_empty(list), "Expected array list is not empty");
    array_list_clear(list);
    TEST_ASSERT_MESSAGE(array_list_is_empty(list), "Expected array list is empty");
    array_list_destroy(list);
}

void linked_list_test() {
    LinkedList* created = linked_list_create(sizeof(int));
    for (int i = 0; i < 16; i++) {
        linked_list_add(created, &i);
    }
    linked_list_destroy(created);
}

void list_test() {
    List* list = list_create(sizeof(int));
    int value;
    for (int i = 0; i < 3; i++) {
        list_add(list, &i);
        TEST_ASSERT_MESSAGE(!list_last(list, &value), "Expected list last succeeds");
        TEST_ASSERT_MESSAGE(i == value, "Expected added list element is last");
    }
    TEST_ASSERT_MESSAGE(EXIT_SUCCESS == list_first(list, &value), "Expected list first succeeds");
    TEST_ASSERT(0 == value);
    TEST_ASSERT_MESSAGE(EXIT_SUCCESS == list_last(list, &value), "Expected list last succeeds");
    TEST_ASSERT_MESSAGE(2 == value, "Expected last element is 2");
    size_t index = 2;
    TEST_ASSERT(EXIT_SUCCESS == list_get(list, index, &value));
    TEST_ASSERT_MESSAGE(2 == value, "Expected element at index 2 is 2");
    TEST_ASSERT_MESSAGE(EXIT_SUCCESS == list_remove_obj(list, &value, &index), "Expected list remove obj succeeds");
    TEST_ASSERT_MESSAGE(2 == index, "Expected removed element is 2");
    TEST_ASSERT_MESSAGE(EXIT_SUCCESS == list_last(list, &value), "Expected list last succeeds");
    TEST_ASSERT(1 == value);
    TEST_ASSERT_MESSAGE(EXIT_FAILURE == list_remove(list, index, &value), "Expected list out of bounds");
    for (int i = list_len(list)-1; i >= 0; i--) {
        TEST_ASSERT(EXIT_SUCCESS == list_remove(list, i, &value));
        TEST_ASSERT(i == value);
    }

    list_destroy(list);
}



int main() {
    UNITY_BEGIN();
    
    RUN_TEST(array_list_test);
    RUN_TEST(linked_list_test);
    RUN_TEST(list_test);

    return UNITY_END();
}
