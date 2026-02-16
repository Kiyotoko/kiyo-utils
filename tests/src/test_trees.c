#include <unity.h>
#include <stdlib.h>

#include "kiyo-collections/b_tree_map.h"
#include "kiyo-collections/b_tree_set.h"

void setUp(void) {}
void tearDown(void) {}

int compere(void* left, void* right) {
  return *(int*)right - *(int*)left;
}

void b_tree_map_test() {
  BTreeMap* tree = b_tree_map_new(sizeof(int), sizeof(int), &compere);
  TEST_ASSERT(0 == b_tree_map_height(tree));
  for (int i = 0; i<32; i++) {
      int a = i*i;
      TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, b_tree_map_put(tree, &i, &a));
  }
  TEST_ASSERT(6 == b_tree_map_height(tree));
  int v;
  int k = 3;
  TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, b_tree_map_get(tree, &k, &v));
  TEST_ASSERT_EQUAL_INT(9, v);
  b_tree_map_free(tree);
}

void b_tree_set_test() {
  BTreeSet* set = b_tree_set_new(sizeof(int), &compere);
  int i = 0;
  for (; i < 3; i++) {
      TEST_ASSERT(EXIT_SUCCESS == b_tree_set_add(set, &i));
  }
  i = 1;
  TEST_ASSERT(b_tree_set_contains(set, &i));
  TEST_ASSERT_MESSAGE(EXIT_UNCHANGED == b_tree_set_add(set, &(i)), "Expected tree unchanged");
  i = 10;
  TEST_ASSERT_MESSAGE(!b_tree_set_contains(set, &i), "Expected tree does not contain element 10");
  b_tree_set_free(set);
}

int main() {
  UNITY_BEGIN();
  
  RUN_TEST(b_tree_map_test);
  RUN_TEST(b_tree_set_test);

  return UNITY_END();
}