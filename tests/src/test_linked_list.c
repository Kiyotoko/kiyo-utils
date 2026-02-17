#include <stdlib.h>
#include <unity.h>

#include "kiyo-collections/linked_list.h"

LinkedList *linked_list;

void setUp(void) { linked_list = linked_list_new(sizeof(int)); }

void tearDown(void) { linked_list_free(linked_list); }

void test_linked_list_add() {
  TEST_ASSERT_EQUAL_INT(0, linked_list_len(linked_list));
  for (int i = 16; i < 32; i++) {
    linked_list_add(linked_list, &i);
  }
  TEST_ASSERT_EQUAL_INT(16, linked_list_len(linked_list));
}

void test_linked_list_push() {
  TEST_ASSERT_EQUAL_INT(0, linked_list_len(linked_list));
  for (int i = 15; i >= 0; i--) {
    linked_list_push(linked_list, &i);
  }
  TEST_ASSERT_EQUAL_INT(16, linked_list_len(linked_list));
}

void test_linked_list_get() {
  for (int i = 0; i < 64; i++) {
    linked_list_add(linked_list, &i);
  }
  int buf;
  for (int i = 0; i < 64; i++) {
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, linked_list_get(linked_list, i, &buf));
    TEST_ASSERT_EQUAL_INT(i, buf);
  }
  TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, linked_list_get(linked_list, -1, &buf));
  TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, linked_list_get(linked_list, 64, &buf));
}

void test_linked_list_pop() {
  TEST_ASSERT_EQUAL_INT(64, linked_list_len(linked_list));
  int buf;
  for (int i = 0; i < 64; i++) {
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, linked_list_pop(linked_list, &buf));
    TEST_ASSERT_EQUAL_INT(i, buf);
  }
  TEST_ASSERT_EQUAL_INT(0, linked_list_len(linked_list));
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_linked_list_add);
  RUN_TEST(test_linked_list_push);
  RUN_TEST(test_linked_list_get);

  return UNITY_END();
}
