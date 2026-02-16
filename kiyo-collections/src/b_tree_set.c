#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "kiyo-collections/b_tree_set.h"

BinaryNode* binary_node_new(void* element, size_t element_size) {
    BinaryNode* created = malloc(sizeof(BinaryNode));
    if (!created) {
        return NULL;
    }

    void* value = malloc(element_size);
    if (!value) {
        free(created);
        return NULL;
    }
    memcpy(value, element, element_size);

    created->value = value;
    created->height = 1;
    created->left = NULL;
    created->right = NULL;
    return created;
}

void binary_node_free(BinaryNode* node) {
    if (node->left) {
        binary_node_free(node->left);
    }
    if (node->right) {
        binary_node_free(node->right);
    }
    free(node->value);
    free(node);
}

void binary_node_update_height(BinaryNode* node) {
    int height_left = node->left ? node->left->height : 0;
    int height_right = node->right ? node->right->height : 0;
    node->height = (height_left > height_right ? height_left : height_right) + 1;
}

BinaryNode* binary_node_rotate_right(BinaryNode* node) {
    BinaryNode *left = node->left;
    node->left = left->right;
    left->right = node;
    
    binary_node_update_height(node);
    binary_node_update_height(left);

    return left;
}

BinaryNode* binary_node_rotate_left(BinaryNode* node) {
    BinaryNode *right = node->right;    
    node->right = right->left;
    right->left = node;
    
    binary_node_update_height(node);
    binary_node_update_height(right);

    return right;
}

int binary_node_get_balance_factor(BinaryNode* node) {
    int height_left = node->left ? node->left->height : 0;
    int height_right = node->right ? node->right->height : 0;
    return height_left - height_right;
}

int binary_node_add(BTreeSet* tree, BinaryNode** origin, void* e) {
    BinaryNode* node = *origin;
    int c = tree->comperator(node->value, e);
    if (c == 0) return EXIT_SUCCESS;

    // Pointer to the node we want to check.
    BinaryNode** target = (c  > 0) ? &(node->right) : &(node->left);
    
    int status;
    if (*target == NULL) {
        *target = binary_node_new(e, tree->element_size);
        tree->len++;
        status = *target == NULL ? EXIT_FAILURE : EXIT_SUCCESS;
    } else {
        status = binary_node_add(tree, target, e);
    }
    binary_node_update_height(node);
    int balance_factor = binary_node_get_balance_factor(node);
    if (balance_factor > 1) {
        if (binary_node_get_balance_factor(node->left) < 0) {
            node->left = binary_node_rotate_left(node->left);
        }
        *origin = binary_node_rotate_right(node);
    } else if (balance_factor < -1) {
        if (binary_node_get_balance_factor(node->right) > 0) {
            node->right = binary_node_rotate_right(node->right);
        }
        *origin = binary_node_rotate_left(node);
    }
    return status;
}

bool binary_node_contains(BTreeSet* tree, BinaryNode* node, void* e) {
    int c = tree->comperator(node->value, e);
    if (c == 0) return true;

    // Pointer to the node we want to check.
    BinaryNode** relevant_child = (c  > 0) ? &(node->right) : &(node->left);
    
    if ((*relevant_child) == NULL) {
        return false;
    } else {
        return binary_node_contains(tree, *relevant_child, e);
    }
}

void binary_node_traverse(BinaryNode* node, Consumer consumer) {
    if (node->left) binary_node_traverse(node->left, consumer);
    consumer(node->value);
    if (node->right) binary_node_traverse(node->right, consumer);
}

BTreeSet* b_tree_set_new(size_t element_size, Comperator comperator) {
    BTreeSet* created = calloc(1, sizeof(BTreeSet));
    created->len = 0;
    created->element_size = element_size;
    created->comperator = comperator;
    return created;
}

void b_tree_set_free(BTreeSet* tree) {
    if (tree->root) binary_node_free(tree->root);

    free(tree);
}

int b_tree_set_add(BTreeSet* tree, void* e) {
    if (tree->root == NULL) {
        tree->root = binary_node_new(e, tree->element_size);
        tree->len++;
        return EXIT_SUCCESS;
    } else {
        return binary_node_add(tree, &(tree->root), e);
    }
}

bool b_tree_set_contains(BTreeSet* tree, void* e) {
    if (tree->root == NULL) return false;

    return binary_node_contains(tree, tree->root, e);
}

void b_tree_set_traverse(BTreeSet* tree, Consumer consumer) {
    if (tree->root) binary_node_traverse(tree->root, consumer);
}

size_t b_tree_set_height(BTreeSet* tree) {
    if (tree->root) return tree->root->height;
    
    return 0;
}
