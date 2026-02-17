#ifndef vec_H
#define vec_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  void *data;
  size_t len;
  size_t capacity;
  size_t element_size;
} Vec;

Vec *vec_new(size_t elment_size);

void vec_free(Vec *linked_list);

void vec_push(Vec *linked_list, void *e);

int vec_get(Vec *linked_list, size_t index, void *buffer);

void vec_grow(Vec *linked_list);

void vec_shrink(Vec *linked_list, size_t new_capacity);

void vec_clear(Vec *linked_list);

size_t vec_len(Vec *linked_list);

bool vec_is_empty(Vec *linked_list);

#endif
