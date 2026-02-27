#include "kiyo-collections/vec.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 16
#define MIN_CAPACITY 4

Vec *vec_new(size_t element_size) {
  Vec *created = malloc(sizeof(Vec));
  if (!created)
    return NULL;

  // Allocate a new array with the default capacity.
  void *array = calloc(DEFAULT_CAPACITY, element_size);
  if (!array) {
    free(created);
    return NULL;
  }
  created->data = array;
  created->len = 0;
  created->capacity = DEFAULT_CAPACITY;
  created->element_size = element_size;

  return created;
}

void vec_free(Vec *vec) {
  free(vec->data);
  free(vec);
}

void vec_push(Vec *vec, void *e) {
  // Check if we have any capacity left. If not, grow the array and then
  // continue.
  if (vec->len >= vec->capacity) {
    vec_grow(vec);
  }
  memcpy((char *)vec->data + vec->len * vec->element_size, e,
         vec->element_size);
  vec->len++;
}

int vec_insert(Vec *vec, size_t index, void *e) {
  if (index == vec->len) {
    vec_push(vec, e);
    return EXIT_SUCCESS;
  }

  if (index < vec->len) {
    if (vec->len >= vec->capacity) {
      vec_grow(vec);
    }
    size_t diff = vec->len - index;
    memmove((char *)vec->data + (index + 1) * vec->element_size,
            (char *)vec->data + index * vec->element_size,
            diff * vec->element_size);
    memcpy((char *)vec->data + index * vec->element_size, e, vec->element_size);
    vec->len++;
    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}

void vec_append(Vec *vec, Vec *other) {
  if (other->len > 0) {
    size_t min_size = vec->len + other->len;
    if (min_size >= vec->capacity) {
      vec->capacity = 1 << (sizeof(size_t) - __builtin_clz(min_size));
      vec_grow(vec);
    }
    memcpy((char *)vec->data + vec->len * vec->element_size, other->data,
           other->len * vec->element_size);
    vec->len += other->len;
  }
}

int vec_remove(Vec *vec, size_t index, void *buffer) {
  if (index < vec->len) {
    memcpy(buffer, (char *)vec->data + index * vec->element_size,
           vec->element_size);
    // If we don't remove the last element, move all elements 1 to the left
    if (index + 1 < vec->len) {
      memmove((char *)vec->data + index * vec->element_size,
              (char *)vec->data + (index + 1) * vec->element_size,
              (vec->len - index - 1) * vec->element_size);
    }
    vec->len--;
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int vec_pop(Vec *vec, void *buffer) {
  size_t index = vec->len - 1;
  if (index < vec->len) {
    memcpy(buffer, (char *)vec->data + index * vec->element_size,
           vec->element_size);
    vec->len--;
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int vec_get(Vec *vec, size_t index, void *buffer) {
  if (index < vec->len) {
    void *data = (char *)vec->data + index * vec->element_size;
    memcpy(buffer, data, vec->element_size);
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

void vec_grow(Vec *vec) {
  // Calculate new capacity. The new capacity is the current capacity doubled.
  int new_capacity = vec->capacity * 2;
  if (new_capacity < MIN_CAPACITY)
    new_capacity = MIN_CAPACITY;

  // Allocate a new array with the new capacity
  void *array = realloc(vec->data, new_capacity * vec->element_size);
  // Failed to allocate memory, return.
  if (!array)
    return;

  vec->data = array;
  vec->capacity = new_capacity;
}

void vec_shrink(Vec *vec, size_t new_capacity) {
  if (new_capacity < vec->len)
    return;
  void *array = realloc(vec->data, new_capacity * vec->element_size);
  // Failed to allocate memory, return.
  if (!array)
    return;

  vec->data = array;
  vec->capacity = new_capacity;
}

void vec_clear(Vec *vec) {
  free(vec->data);
  vec->capacity = MIN_CAPACITY;
  vec->len = 0;
  void *array = calloc(vec->capacity, vec->element_size);
  // Failed to allocate memory, return.
  if (!array)
    return;
  vec->data = array;
}

size_t vec_len(Vec *vec) { return vec->len; }

bool vec_is_empty(Vec *vec) { return vec->len == 0; }
