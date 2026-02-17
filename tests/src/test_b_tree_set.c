#include <stdlib.h>
#include <unity.h>

#include "kiyo-collections/b_tree_set.h"

BTreeSet *tree_set;

int compere(void *left, void *right) { return *(int *)right - *(int *)left; }

void setUp(void) { tree_set = b_tree_set_new(sizeof(int), &compere); }

void tearDown(void) { b_tree_set_free(tree_set); }

void test_b_tree_set_add() {
  TEST_ASSERT_EQUAL_INT(0, tree_set->len);
  for (int i = 0; i < 32; i++) {
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, b_tree_set_add(tree_set, &i));
  }
  TEST_ASSERT_EQUAL_INT(32, tree_set->len);
}

void test_b_tree_set_contains() {
  for (int i = 0; i < 32; i++) {
    b_tree_set_add(tree_set, &i);
  }

  int i = 0;
  for (; i < 32; i++) {
    TEST_ASSERT(b_tree_set_contains(tree_set, &i));
  }
  i = -1;
  TEST_ASSERT_FALSE(b_tree_set_contains(tree_set, &i));
  i = 33;
  TEST_ASSERT_FALSE(b_tree_set_contains(tree_set, &i));
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_b_tree_set_add);
  RUN_TEST(test_b_tree_set_contains);

  return UNITY_END();
}