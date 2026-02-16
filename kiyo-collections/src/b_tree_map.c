#include <string.h>
#include <stdlib.h>
#include "kiyo-collections/b_tree_map.h"

BinaryEntry* binary_entry_new(void* key, void* value, int key_size, int value_size) {
    BinaryEntry* created = malloc(sizeof(BinaryEntry));
    if (!created) {
        return NULL;
    }

    void* mkey = malloc(key_size);
    if (!mkey) {
        free(created);
        return NULL;
    }
    void* mvalue = malloc(value_size);
    if (!mvalue) {
        free(created);
        free(mkey);
        return NULL;
    }
    memcpy(mkey, key, key_size);
    memcpy(mvalue, value, value_size);

    created->key = mkey;
    created->value = mvalue;
    created->height = 1;
    created->left = NULL;
    created->right = NULL;
    return created;
}

void binary_entry_free(BinaryEntry* node) {
    if (node->left) {
        binary_entry_free(node->left);
    }
    if (node->right) {
        binary_entry_free(node->right);
    }
    free(node->key);
    free(node->value);
    free(node);
}

void binary_entry_update_height(BinaryEntry* node) {
    int height_left = node->left ? node->left->height : 0;
    int height_right = node->right ? node->right->height : 0;
    node->height = (height_left > height_right ? height_left : height_right) + 1;
}

// TODO: fix rotation
void binary_entry_rotate_right(BinaryEntry* node) {
    // Swap values around
    void* root = node->value;
    node->value = node->left->value;
    node->key = node->left->value;
    node->left->value = root;

    // Move subtrees
    BinaryEntry* rotate1 = node->right;
    BinaryEntry* rotate2 = node->left->right;
    node->right = node->left;
    node->right->right = rotate1;
    rotate1 = node->left->left;
    node->right->left = rotate2;
    node->left = rotate1;

    binary_entry_update_height(node->left);
    binary_entry_update_height(node->right);
    binary_entry_update_height(node);
}

void binary_entry_rotate_left(BinaryEntry* node) {
    // Swap values around
    void* root = node->value;
    node->value = node->right->value;
    node->right->value = root;

    // Move subtrees
    BinaryEntry* rotate1 = node->left;
    BinaryEntry* rotate2 = node->right->left;
    node->left = node->right;
    node->left->left = rotate1;
    rotate1 = node->right->right;
    node->left->right = rotate2;
    node->right = rotate1;

    binary_entry_update_height(node->left);
    binary_entry_update_height(node->right);
    binary_entry_update_height(node);
}

int binary_entry_get_balance_factor(BinaryEntry* node) {
    int height_left = node->left ? node->left->height : 0;
    int height_right = node->right ? node->right->height : 0;
    return height_left - height_right;
}

int binary_entry_put(BTreeMap* tree, BinaryEntry* node, void* k, void* v) {
    int c = tree->comperator(node->key, k);
    if (c == 0) {
        if (node->value == v) return EXIT_UNCHANGED;
        memcpy(node->value, v, tree->value_size);
        return EXIT_SUCCESS;
    }

    // Pointer to the node we want to check.
    BinaryEntry** relevant_child = (c  > 0) ? &(node->right) : &(node->left);
    
    int status;
    if ((*relevant_child) == NULL) {
        *relevant_child = binary_entry_new(k, v, tree->key_size, tree->value_size);
        status = *relevant_child == NULL ? EXIT_FAILURE : EXIT_SUCCESS;
    } else {
        status = binary_entry_put(tree, *relevant_child, k, v);
    }
    binary_entry_update_height(node);
    int balance_factor = binary_entry_get_balance_factor(node);
    if (balance_factor > 1) {
        if (binary_entry_get_balance_factor(node->left) < 0) binary_entry_rotate_left(node->left);
        binary_entry_rotate_right(node);
    } else if (balance_factor < -1) {
        if (binary_entry_get_balance_factor(node->right) > 0) binary_entry_rotate_right(node->right);
        binary_entry_rotate_left(node);
    }
    return status;
}

int binary_entry_get(BTreeMap* tree, BinaryEntry* node, void* k, void* v) {
    int c = tree->comperator(node->key, k);
    if (c == 0) {
        memcpy(v, node->value, tree->value_size);
        return EXIT_SUCCESS;
    } else {
        BinaryEntry* relevant_child = (c  > 0) ? node->right : node->left;
        if (relevant_child == NULL) return EXIT_FAILURE;
        return binary_entry_get(tree, relevant_child, k, v);
    }
}

bool binary_entry_contains(BTreeMap* tree, BinaryEntry* node, void* e) {
    int c = tree->comperator(node->key, e);
    if (c == 0) return true;

    // Pointer to the node we want to check.
    BinaryEntry** relevant_child = (c  > 0) ? &(node->right) : &(node->left);
    
    if ((*relevant_child) == NULL) {
        return false;
    } else {
        return binary_entry_contains(tree, *relevant_child, e);
    }
}

BTreeMap* b_tree_map_new(int key_size, int value_size, Comperator comperator) {
    BTreeMap* created = calloc(1, sizeof(BTreeMap));
    created->key_size = key_size;
    created->value_size = value_size;
    created->comperator = comperator;
    return created;
}

void b_tree_map_free(BTreeMap* tree) {
    if (tree->root) binary_entry_free(tree->root);

    free(tree);
}

int b_tree_map_put(BTreeMap* tree, void* k, void* v) {
    if (tree->root == NULL) {
        tree->root = binary_entry_new(k, v, tree->key_size, tree->value_size);
        return EXIT_SUCCESS;
    } else {
        return binary_entry_put(tree, tree->root, k, v);
    }
}

int b_tree_map_get(BTreeMap* tree, void* k, void* v) {
    if (tree->root == NULL) return EXIT_FAILURE;

    return binary_entry_get(tree, tree->root, k, v);
}

bool b_tree_map_contains(BTreeMap* tree, void* e) {
    if (tree->root == NULL) return false;

    return binary_entry_contains(tree, tree->root, e);
}

size_t b_tree_map_height(BTreeMap* tree) {
    if (tree->root) return tree->root->height;
    
    return 0;
}
