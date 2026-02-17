#include <stdlib.h>
#include <unity.h>

#include "kiyo-collections/vec.h"

Vec *vec;

void setUp(void) { vec = vec_new(sizeof(int)); }

void tearDown(void) { vec_free(vec); }

void test_vec_push() {
  TEST_ASSERT(vec_is_empty(vec));
  for (int i = 0; i < 64; i++) {
    vec_push(vec, &i);
  }
  TEST_ASSERT_EQUAL_INT(64, vec_len(vec));
}

void test_vec_get() {
  int buf;
  for (int i = 0; i < vec_len(vec); i++) {
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, vec_get(vec, i, &buf));
    TEST_ASSERT_EQUAL_INT(i, buf);
  }
  TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, vec_get(vec, -1, &buf));
  TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, vec_get(vec, 64, &buf));
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_vec_push);
  RUN_TEST(test_vec_get);

  return UNITY_END();
}
