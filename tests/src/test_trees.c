#include <unity.h>
#include <stdlib.h>

#include "kiyo-collections/binary_tree.h"
#include "kiyo-collections/tree_set.h"

void setUp(void) {}
void tearDown(void) {}

int compere(void* left, void* right) {
  return *(int*)right - *(int*)left;
}

void binary_tree_test() {
  BinaryTree* tree = binary_tree_create(sizeof(int), &compere);
  TEST_ASSERT(0 == binary_tree_height(tree));
  for (int i = 0; i<32; i++) {
      binary_tree_add(tree, &i);
  }
  TEST_ASSERT(6 == binary_tree_height(tree));
  binary_tree_destroy(tree);
}

void tree_set_test() {
  TreeSet* set = tree_set_create(sizeof(int), &compere);
  TEST_ASSERT(0 == tree_set_size(set));
  int i = 0;
  for (; i < 3; i++) {
      TEST_ASSERT(EXIT_SUCCESS == tree_set_add(set, &i));
  }
  TEST_ASSERT(3 == tree_set_size(set));
  i = 1;
  TEST_ASSERT(tree_set_contains(set, &i));
  TEST_ASSERT_MESSAGE(EXIT_UNCHANGED == tree_set_add(set, &(i)), "Expected tree unchanged");
  i = 10;
  TEST_ASSERT_MESSAGE(!tree_set_contains(set, &i), "Expected tree does not contain element 10");
  tree_set_destroy(set);
}

int main() {
  UNITY_BEGIN();
  
  RUN_TEST(binary_tree_test);
  RUN_TEST(tree_set_test);

  return UNITY_END();
}