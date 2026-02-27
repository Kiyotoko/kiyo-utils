#include <stdlib.h>
#include <unity.h>

#include "kiyo-collections/vec.h"
#include "unity_internals.h"

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

void test_vec_insert() {
  int i = 0;
  TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, vec_insert(vec, 1, &i));
  vec_push(vec, &i);
  int buf;
  for (i = 0; i < 32; i++) {
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, vec_insert(vec, 1, &i));
    vec_get(vec, 1, &buf);
    TEST_ASSERT_EQUAL_INT(i, buf);
  }
  TEST_ASSERT_EQUAL_INT(1 + 32, vec_len(vec));
}

void test_vec_append() {
  Vec *other = vec_new(sizeof(int));
  for (int i = 0; i < 32; i++) {
    vec_push(vec, &i);
    vec_push(other, &i);
  }
  vec_append(vec, other);
  TEST_ASSERT_EQUAL_INT(64, vec_len(vec));
  int buf;
  for (int i = 32; i < 64; i++) {
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, vec_get(vec, i, &buf));
    TEST_ASSERT_EQUAL_INT(i - 32, buf);
  }
  vec_free(other);
}

void test_vec_remove() {
  int buf;
  TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, vec_remove(vec, 0, &buf));
  for (int i = 0; i < 32; i++) {
    vec_push(vec, &i);
  }
  TEST_ASSERT_EQUAL_INT(32, vec_len(vec));
  TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, vec_remove(vec, 15, &buf));
  TEST_ASSERT_EQUAL_INT(15, buf);
  TEST_ASSERT_EQUAL_INT(31, vec_len(vec));
  for (int i = 15; i < 31; i++) {
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, vec_get(vec, i, &buf));
    TEST_ASSERT_EQUAL_INT(i + 1, buf);
  }
}

void test_vec_pop() {
  TEST_ASSERT_EQUAL_INT(0, vec_len(vec));
  int buf;
  TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, vec_pop(vec, &buf));
  for (int i = 0; i < 32; i++) {
    vec_push(vec, &i);
  }
  TEST_ASSERT_EQUAL_INT(32, vec_len(vec));
  for (int i = 31; i >= 0; i--) {
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, vec_pop(vec, &buf));
    TEST_ASSERT_EQUAL_INT(i, buf);
  }
  TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, vec_pop(vec, &buf));
  TEST_ASSERT_EQUAL_INT(0, vec_len(vec));
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

void test_vec_clear() {
  vec_clear(vec);
  for (int i = 0; i < 32; i++) {
    vec_push(vec, &i);
  }
  TEST_ASSERT_EQUAL_INT(32, vec_len(vec));
  vec_clear(vec);
  for (int i = 0; i < 32; i++) {
    vec_push(vec, &i);
  }
  TEST_ASSERT_EQUAL_INT(32, vec_len(vec));
  vec_clear(vec);
}

void test_vec_grow_shrink() {
  TEST_ASSERT_EQUAL_INT(16, vec_capacity(vec));
  for (int i = 0; i < 32; i++) {
    vec_push(vec, &i);
  }
  TEST_ASSERT_EQUAL_INT(32, vec_len(vec));
  TEST_ASSERT_EQUAL_INT(32, vec_capacity(vec));
  vec_grow(vec);
  TEST_ASSERT_EQUAL_INT(64, vec_capacity(vec));
  vec_shrink(vec, 32);
  TEST_ASSERT_EQUAL_INT(32, vec_capacity(vec));
  int buf;
  for (int i = 0; i < 32; i++) {
    vec_get(vec, i, &buf);
    TEST_ASSERT_EQUAL_INT(i, buf);
  }
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_vec_push);
  RUN_TEST(test_vec_insert);
  RUN_TEST(test_vec_append);
  RUN_TEST(test_vec_remove);
  RUN_TEST(test_vec_pop);
  RUN_TEST(test_vec_get);
  RUN_TEST(test_vec_clear);
  RUN_TEST(test_vec_grow_shrink);

  return UNITY_END();
}
