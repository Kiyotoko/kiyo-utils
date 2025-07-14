#include <stdlib.h>
#include "tree_set.h"

TreeSet* tree_set_create(int element_size, Comperator comperator) {
    TreeSet* created = malloc(sizeof(TreeSet));
    if (!created) {
        return NULL;
    }
    BinaryTree* binary_tree = binary_tree_create(element_size, comperator);
    if (!binary_tree) {
        free(created);
        return NULL;
    }
    created->tree = binary_tree;
    created->size = 0;
    return created;
}

void tree_set_destroy(TreeSet* tree) {
    binary_tree_destroy(tree->tree);
    free(tree);
}

int tree_set_add(TreeSet* tree, void* e) {
    int status = binary_tree_add(tree->tree, e);
    if (status == EXIT_SUCCESS) tree->size++;
    return status;
}

bool tree_set_contains(TreeSet* tree, void* e) {
    return binary_tree_contains(tree->tree, e);
}

size_t tree_set_size(TreeSet* tree) {
    return tree->size;
}
