#ifndef b_tree_set_H
#define b_tree_set_H

#include <stddef.h>
#include <stdbool.h>
#include "functions.h"

typedef struct BinaryNode {
    void* value;
    struct BinaryNode* left;
    struct BinaryNode* right;
    size_t height;
} BinaryNode;

typedef struct {
    BinaryNode* root;
    int element_size;
    Comperator comperator;
} BTreeSet;

BTreeSet* b_tree_set_new(int element_size, Comperator comperator);

void b_tree_set_free(BTreeSet* tree);

#define EXIT_UNCHANGED -1

int b_tree_set_add(BTreeSet* tree, void* e);

int b_tree_set_remove(BTreeSet* tree, void* e);

bool b_tree_set_contains(BTreeSet* tree, void* e);

void b_tree_set_traverse(BTreeSet* tree, Consumer consumer);

size_t b_tree_set_height(BTreeSet* tree);

#endif
