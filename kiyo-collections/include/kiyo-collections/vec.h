#ifndef VEC_H
#define VEC_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  void *data;
  size_t len;
  size_t capacity;
  size_t element_size;
} Vec;

Vec *vec_new(size_t element_size);

void vec_free(Vec *vec);

void vec_push(Vec *vec, void *e);

int vec_insert(Vec *vec, size_t index, void *e);

void vec_append(Vec *vec, Vec *other);

int vec_remove(Vec *vec, size_t index, void *buffer);

int vec_pop(Vec *vec, void *buffer);

int vec_get(Vec *vec, size_t index, void *buffer);

void vec_grow(Vec *vec);

void vec_shrink(Vec *vec, size_t new_capacity);

size_t vec_len(Vec *vec);

size_t vec_capacity(Vec *vec);

bool vec_is_empty(Vec *vec);

void vec_clear(Vec *vec);

#endif
