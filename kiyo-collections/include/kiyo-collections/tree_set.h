#ifndef TREE_SET_H
#define TREE_SET_H

#include "binary_tree.h"

typedef struct {
    BinaryTree* tree;
    size_t size;
} TreeSet;

TreeSet* tree_set_create(int element_size, Comperator comperator);

void tree_set_destroy(TreeSet* tree);

int tree_set_add(TreeSet* tree, void* e);

bool tree_set_contains(TreeSet* tree, void* e);

size_t tree_set_size(TreeSet* tree);

#endif