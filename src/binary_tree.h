#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdint.h>
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
} BinaryTree;

BinaryTree* binary_tree_create(int element_size, Comperator comperator);

void binary_tree_destroy(BinaryTree* tree);

#define EXIT_UNCHANGED -1

int binary_tree_add(BinaryTree* tree, void* e);

bool binary_tree_contains(BinaryTree* tree, void* e);

void binary_tree_traverse(BinaryTree* tree, Consumer consumer);

size_t binary_tree_height(BinaryTree* tree);

#endif
