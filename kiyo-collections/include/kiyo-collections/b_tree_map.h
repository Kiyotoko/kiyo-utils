#ifndef b_tree_map_H
#define b_tree_map_H

#include "functions.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct BinaryEntry {
  void *key;
  void *value;
  struct BinaryEntry *left;
  struct BinaryEntry *right;
  size_t height;
} BinaryEntry;

typedef struct {
  BinaryEntry *root;
  size_t len;
  size_t key_size;
  size_t value_size;
  Comperator comperator;
} BTreeMap;

BTreeMap *b_tree_map_new(size_t key_size, size_t value_size,
                         Comperator comperator);

void b_tree_map_free(BTreeMap *tree);

int b_tree_map_put(BTreeMap *tree, void *k, void *v);

int b_tree_map_get(BTreeMap *tree, void *k, void *v);

int b_tree_map_remove(BTreeMap *tree, void *k);

bool b_tree_map_contains_key(BTreeMap *tree, void *k);

void b_tree_map_clear(BTreeMap *tree);

size_t b_tree_map_height(BTreeMap *tree);

#endif
