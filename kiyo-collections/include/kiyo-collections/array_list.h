#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    void* data;
    size_t len;
    size_t capacity;
    size_t element_size;
} ArrayList;

ArrayList* array_list_create(size_t elment_size);

void array_list_destroy(ArrayList* list);

void array_list_add(ArrayList* list, void* e);

int array_list_get(ArrayList* list, size_t index, void* buffer);

void array_list_grow(ArrayList* list);

void array_list_shrink(ArrayList* list, size_t new_capacity);

void array_list_clear(ArrayList* list);

size_t array_list_len(ArrayList* list);

bool array_list_is_empty(ArrayList* list);

#endif
