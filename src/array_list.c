#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "array_list.h"

#define DEFAULT_CAPACITY 16
#define MIN_CAPACITY 4

ArrayList* array_list_create(size_t element_size) {
    ArrayList* created = calloc(1, sizeof(ArrayList));
    if (!created) return NULL;

    // Allocate a new array with the default capacity.
    int* array = calloc(DEFAULT_CAPACITY, element_size);
    if (!array) {
        free(created);
        return NULL;
    }
    created->data = array;
    created->capacity = DEFAULT_CAPACITY;
    created->element_size = element_size;
    
    return created;
}

void array_list_destroy(ArrayList* list) {
    free(list->data);
    free(list);
}

void array_list_add(ArrayList* list, void* e) {
    // Check if we have any capacity left. If not, grow the array and then continue.
    if (list->len >= list->capacity) {
        array_list_grow(list);
    }
    memcpy(list->data + list->len * list->element_size, e, list->element_size);
    list->len++;
}

int array_list_get(ArrayList* list, size_t index, void* buffer) {
    if (0 <= index && index < list->len) {
        void* data = list->data + index * list->element_size;
        memcpy(buffer, data, list->element_size);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

void array_list_grow(ArrayList* list) {
    // Calculate new capacity. The new capacity is the current capacity doubled.
    int new_capacity = list->capacity * 2;
    if (new_capacity < MIN_CAPACITY) new_capacity = MIN_CAPACITY;
    
    // Allocate a new array with the new capacity
    void* array = realloc(list->data, new_capacity * list->element_size);
    // Failed to allocate memory, return.
    if (!array) return;

    list->data = array;
    list->capacity = new_capacity;
}

void array_list_shrink(ArrayList* list, size_t new_capacity) {
    if (new_capacity < list->len) return;
    void* array = realloc(list->data, new_capacity * list->element_size);
    // Failed to allocate memory, return.
    if (!array) return;

    list->data = array;
    list->capacity = new_capacity;
}

void array_list_clear(ArrayList* list) {
    free(list->data);
    list->capacity = MIN_CAPACITY;
    list->len = 0;
    void* array = calloc(list->capacity, list->element_size);
    // Failed to allocate memory, return.
    if (!array) return;
    list->data = array;
}

size_t array_list_len(ArrayList* list) {
    return list->len;
}

bool array_list_is_empty(ArrayList* list) {
    return list->len == 0;
}
