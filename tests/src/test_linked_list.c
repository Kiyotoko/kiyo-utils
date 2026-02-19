#include <stddef.h>
#include <stdlib.h>
#include <unity.h>

#include "kiyo-collections/linked_list.h"

LinkedList *linked_list;

void setUp(void) { linked_list = linked_list_new(sizeof(int)); }

void tearDown(void) { linked_list_free(linked_list); }

void test_linked_list_push_front() {
  TEST_ASSERT_EQUAL_INT(0, linked_list_len(linked_list));
  for (int i = 16; i < 32; i++) {
    linked_list_push_front(linked_list, &i);
    TEST_ASSERT_EQUAL_MEMORY(&i, linked_list->head->value, sizeof(int));
  }
  TEST_ASSERT_EQUAL_INT(16, linked_list_len(linked_list));
}

void test_linked_list_push_back() {
  TEST_ASSERT_EQUAL_INT(0, linked_list_len(linked_list));
  for (int i = 15; i >= 0; i--) {
    linked_list_push_back(linked_list, &i);
    TEST_ASSERT_EQUAL_MEMORY(&i, linked_list->tail->value, sizeof(int));
  }
  TEST_ASSERT_EQUAL_INT(16, linked_list_len(linked_list));
}

void test_linked_list_get() {
  for (int i = 0; i < 64; i++) {
    linked_list_push_back(linked_list, &i);
  }
  int buf;
  for (int i = 0; i < 64; i++) {
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, linked_list_get(linked_list, i, &buf));
    TEST_ASSERT_EQUAL_INT(i, buf);
  }
  TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, linked_list_get(linked_list, -1, &buf));
  TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, linked_list_get(linked_list, 64, &buf));
}

void test_linked_list_pop_front() {
  for (int i = 0; i < 64; i++) {
    linked_list_push_back(linked_list, &i);
  }
  TEST_ASSERT_EQUAL_INT(64, linked_list_len(linked_list));
  int buf;
  for (int i = 0; i < 64; i++) {
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, linked_list_pop_front(linked_list, &buf));
    TEST_ASSERT_EQUAL_INT(i, buf);
  }
  TEST_ASSERT_EQUAL_INT(0, linked_list_len(linked_list));
}

void test_linked_list_pop_back() {
  for (int i = 0; i < 64; i++) {
    linked_list_push_back(linked_list, &i);
  }
  TEST_ASSERT_EQUAL_INT(64, linked_list_len(linked_list));
  int buf;
  for (int i = 63; i >= 0; i--) {
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, linked_list_pop_back(linked_list, &buf));
    TEST_ASSERT_EQUAL_INT(i, buf);
  }
  TEST_ASSERT_EQUAL_INT(0, linked_list_len(linked_list));
}

void test_linked_list_remove() {
  for (int i = 0; i < 64; i++) {
    linked_list_push_back(linked_list, &i);
  }
  TEST_ASSERT_EQUAL_INT(64, linked_list_len(linked_list));
  int buf;
  TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, linked_list_remove(linked_list, 3, &buf));
  TEST_ASSERT_EQUAL_INT(3, buf);
  TEST_ASSERT_EQUAL_INT(63, linked_list_len(linked_list));

  TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, linked_list_remove(linked_list, 63, &buf));

  TEST_ASSERT_EQUAL_INT(63, linked_list_len(linked_list));
}

bool greater_eq_10(void *v) {
  return *(int*)v >= 10;
}

void test_linked_list_remove_if() {
  for (int i = 0; i < 64; i++) {
    linked_list_push_back(linked_list, &i);
  }
  TEST_ASSERT_EQUAL_INT(64, linked_list_len(linked_list));
  linked_list_remove_if(linked_list, greater_eq_10);
  TEST_ASSERT_EQUAL_INT(10, linked_list_len(linked_list));
  linked_list_remove_if(linked_list, greater_eq_10);
  TEST_ASSERT_EQUAL_INT(10, linked_list_len(linked_list));
}

void test_linked_list_is_empty() {
  TEST_ASSERT(linked_list_is_empty(linked_list));
  int i = 0;
  linked_list_push_back(linked_list, &i);
  TEST_ASSERT_FALSE(linked_list_is_empty(linked_list));
  linked_list_pop_front(linked_list, &i);
  TEST_ASSERT(linked_list_is_empty(linked_list));
}

void test_linked_list_clear() {
  for (int i = 0; i < 64; i++) {
    linked_list_push_back(linked_list, &i);
  }
  TEST_ASSERT_EQUAL_INT(64, linked_list_len(linked_list));
  linked_list_clear(linked_list);
  TEST_ASSERT_EQUAL_INT(0, linked_list_len(linked_list));
  for (int i = 0; i < 64; i++) {
    linked_list_push_back(linked_list, &i);
  }
  TEST_ASSERT_EQUAL_INT(64, linked_list_len(linked_list));
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_linked_list_push_front);
  RUN_TEST(test_linked_list_push_back);
  RUN_TEST(test_linked_list_get);
  RUN_TEST(test_linked_list_pop_front);
  RUN_TEST(test_linked_list_pop_back);
  RUN_TEST(test_linked_list_remove);
  RUN_TEST(test_linked_list_remove_if);
  RUN_TEST(test_linked_list_is_empty);
  RUN_TEST(test_linked_list_clear);

  return UNITY_END();
}
