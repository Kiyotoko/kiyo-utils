#include <stdlib.h>
#include <unity.h>

#include "kiyo-collections/linked_list.h"
#include "kiyo-collections/vec.h"

void setUp(void) {}
void tearDown(void) {}

void vec_test() {
  Vec *vec = vec_new(sizeof(int));
  TEST_ASSERT(0 == vec_len(vec));
  TEST_ASSERT(vec_is_empty(vec));
  for (int i = 0; i < 64; i++) {
    vec_push(vec, &i);
  }
  TEST_ASSERT(64 == vec_len(vec));
  for (int i = 0; i < vec_len(vec); i++) {
    int a;
    TEST_ASSERT_MESSAGE(EXIT_SUCCESS == vec_get(vec, i, &a),
                        "Expected vec could get element");
    TEST_ASSERT(i == a);
  }
  TEST_ASSERT_MESSAGE(!vec_is_empty(vec), "Expected array vec is not empty");
  vec_clear(vec);
  TEST_ASSERT_MESSAGE(vec_is_empty(vec), "Expected array vec is empty");
  vec_free(vec);
}

void linked_list_test() {
  LinkedList *linked_list = linked_list_new(sizeof(int));
  for (int i = 0; i < 16; i++) {
    linked_list_add(linked_list, &i);
  }
  linked_list_free(linked_list);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(vec_test);
  RUN_TEST(linked_list_test);

  return UNITY_END();
}
