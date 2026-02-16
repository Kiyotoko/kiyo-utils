#ifndef b_tree_map_H
#define b_tree_map_H

#include <stddef.h>
#include <stdbool.h>
#include "functions.h"

typedef struct BinaryEntry {
    void* key;
    void* value;
    struct BinaryEntry* left;
    struct BinaryEntry* right;
    size_t height;
} BinaryEntry;

typedef struct {
    BinaryEntry* root;
    int key_size;
    int value_size;
    Comperator comperator;
} BTreeMap;

BTreeMap* b_tree_map_new(int key_size, int value_size, Comperator comperator);

void b_tree_map_free(BTreeMap* tree);

#define EXIT_UNCHANGED -1

int b_tree_map_put(BTreeMap* tree, void* k, void* v);

int b_tree_map_remove(BTreeMap* tree, void* k);

bool b_tree_map_contains_key(BTreeMap* tree, void* k);

bool b_tree_map_contains_value(BTreeMap* tree, void* k);

size_t b_tree_map_height(BTreeMap* tree);

#endif
