#include <stdlib.h>
#include <unity.h>

#include "kiyo-collections/b_tree_map.h"

BTreeMap *tree_map;

int compere(void *left, void *right) { return *(int *)right - *(int *)left; }

void setUp(void) {
  tree_map = b_tree_map_new(sizeof(int), sizeof(int), &compere);
}

void tearDown(void) { b_tree_map_free(tree_map); }

void test_b_tree_map_put() {
  TEST_ASSERT_EQUAL_INT(0, tree_map->len);
  for (int k = 0; k < 32; k++) {
    int v = k * k;
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, b_tree_map_put(tree_map, &k, &v));
  }
  TEST_ASSERT_EQUAL_INT(32, tree_map->len);
  TEST_ASSERT_EQUAL_INT(6, tree_map->root->height);
}

void test_b_tree_map_contains() {
  for (int k = 0; k < 32; k++) {
    int v = k * k;
    b_tree_map_put(tree_map, &k, &v);
  }

  int k = 0;
  for (; k < 32; k++) {
    TEST_ASSERT(b_tree_map_contains_key(tree_map, &k));
  }
  k = -1;
  TEST_ASSERT_FALSE(b_tree_map_contains_key(tree_map, &k));
  k = 32;
  TEST_ASSERT_FALSE(b_tree_map_contains_key(tree_map, &k));
}

void test_b_tree_map_get() {
  for (int k = 0; k < 32; k++) {
    int v = k * k;
    b_tree_map_put(tree_map, &k, &v);
  }

  int v;
  int k = 3;
  TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, b_tree_map_get(tree_map, &k, &v));
  TEST_ASSERT_EQUAL_INT(9, v);
  k = 32;
  TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, b_tree_map_get(tree_map, &k, &v));
  k = 10;
  TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, b_tree_map_get(tree_map, &k, &v));
  TEST_ASSERT_EQUAL_INT(100, v);
}

void test_b_tree_map_put_unbalanced() {
  b_tree_map_clear(tree_map);
  int k = 0;
  b_tree_map_put(tree_map, &k, &k);
  k = 2;
  b_tree_map_put(tree_map, &k, &k);
  k = 1;
  b_tree_map_put(tree_map, &k, &k);
  TEST_ASSERT_EQUAL_INT(1, *((int *)tree_map->root->value));
  TEST_ASSERT_EQUAL_INT(0, *((int *)tree_map->root->left->value));
  TEST_ASSERT_EQUAL_INT(2, *((int *)tree_map->root->right->value));
  for (int i = 0; i < 3; i++) {
    TEST_ASSERT(b_tree_map_contains_key(tree_map, &i));
  }
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_b_tree_map_put);
  RUN_TEST(test_b_tree_map_contains);
  RUN_TEST(test_b_tree_map_get);
  RUN_TEST(test_b_tree_map_put_unbalanced);

  return UNITY_END();
}