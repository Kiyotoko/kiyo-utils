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

BinaryEntry* binary_entry_rotate_right(BinaryEntry* node) {
    BinaryEntry *left = node->left;
    node->left = left->right;
    left->right = node;
    
    binary_entry_update_height(node);
    binary_entry_update_height(left);

    return left;
}

BinaryEntry* binary_entry_rotate_left(BinaryEntry* node) {
    BinaryEntry *right = node->right;    
    node->right = right->left;
    right->left = node;
    
    binary_entry_update_height(node);
    binary_entry_update_height(right);

    return right;
}

int binary_entry_get_balance_factor(BinaryEntry* node) {
    int height_left = node->left ? node->left->height : 0;
    int height_right = node->right ? node->right->height : 0;
    return height_left - height_right;
}

int binary_entry_put(BTreeMap* tree, BinaryEntry** origin, void* k, void* v) {
    BinaryEntry* node = *origin;
    int c = tree->comperator(node->key, k);
    if (c == 0) {
        if (node->value == v) return EXIT_UNCHANGED;
        memcpy(node->value, v, tree->value_size);
        return EXIT_SUCCESS;
    }

    // Pointer to the node we want to check.
    BinaryEntry** target = (c  > 0) ? &(node->right) : &(node->left);
    
    int status;
    if (*target == NULL) {
        *target = binary_entry_new(k, v, tree->key_size, tree->value_size);
        tree->len++;
        status = *target == NULL ? EXIT_FAILURE : EXIT_SUCCESS;
    } else {
        status = binary_entry_put(tree, target, k, v);
    }
    binary_entry_update_height(node);
    int balance_factor = binary_entry_get_balance_factor(node);
    if (balance_factor > 1) {
        if (binary_entry_get_balance_factor(node->left) < 0) {
            node->left = binary_entry_rotate_left(node->left);
        }
        *origin = binary_entry_rotate_right(node);
    } else if (balance_factor < -1) {
        if (binary_entry_get_balance_factor(node->right) > 0) {
            node->right = binary_entry_rotate_right(node->right);
        }
        *origin = binary_entry_rotate_left(node);
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

bool binary_entry_contains_key(BTreeMap* tree, BinaryEntry* node, void* e) {
    int c = tree->comperator(node->key, e);
    if (c == 0) return true;

    // Pointer to the node we want to check.
    BinaryEntry** relevant_child = (c  > 0) ? &(node->right) : &(node->left);
    
    if ((*relevant_child) == NULL) {
        return false;
    } else {
        return binary_entry_contains_key(tree, *relevant_child, e);
    }
}

BTreeMap* b_tree_map_new(size_t key_size, size_t value_size, Comperator comperator) {
    BTreeMap* created = calloc(1, sizeof(BTreeMap));
    created->len = 0;
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
        tree->len++;
        return EXIT_SUCCESS;
    } else {
        return binary_entry_put(tree, &(tree->root), k, v);
    }
}

int b_tree_map_get(BTreeMap* tree, void* k, void* v) {
    if (tree->root == NULL) return EXIT_FAILURE;

    return binary_entry_get(tree, tree->root, k, v);
}

bool b_tree_map_contains_key(BTreeMap* tree, void* e) {
    if (tree->root == NULL) return false;

    return binary_entry_contains_key(tree, tree->root, e);
}

void b_tree_map_clear(BTreeMap *tree) {
    if (tree->root != NULL) {
        binary_entry_free(tree->root);
        tree->root = NULL;
        tree->len = 0;
    }
}

size_t b_tree_map_height(BTreeMap* tree) {
    if (tree->root) return tree->root->height;
    
    return 0;
}
