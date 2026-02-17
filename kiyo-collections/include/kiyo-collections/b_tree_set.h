#ifndef b_tree_set_H
#define b_tree_set_H

#include "functions.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct BinaryNode {
  void *value;
  struct BinaryNode *left;
  struct BinaryNode *right;
  size_t height;
} BinaryNode;

typedef struct {
  BinaryNode *root;
  size_t len;
  size_t element_size;
  Comperator comperator;
} BTreeSet;

BTreeSet *b_tree_set_new(size_t element_size, Comperator comperator);

void b_tree_set_free(BTreeSet *tree);

int b_tree_set_add(BTreeSet *tree, void *e);

int b_tree_set_remove(BTreeSet *tree, void *e);

bool b_tree_set_contains(BTreeSet *tree, void *e);

size_t b_tree_set_len(BTreeSet *tree);

#endif
