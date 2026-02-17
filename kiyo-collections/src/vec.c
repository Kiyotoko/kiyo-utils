#include "kiyo-collections/vec.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 16
#define MIN_CAPACITY 4

Vec *vec_new(size_t element_size) {
  Vec *created = calloc(1, sizeof(Vec));
  if (!created)
    return NULL;

  // Allocate a new array with the default capacity.
  void *array = calloc(DEFAULT_CAPACITY, element_size);
  if (!array) {
    free(created);
    return NULL;
  }
  created->data = array;
  created->capacity = DEFAULT_CAPACITY;
  created->element_size = element_size;

  return created;
}

void vec_free(Vec *linked_list) {
  free(linked_list->data);
  free(linked_list);
}

void vec_push(Vec *linked_list, void *e) {
  // Check if we have any capacity left. If not, grow the array and then
  // continue.
  if (linked_list->len >= linked_list->capacity) {
    vec_grow(linked_list);
  }
  memcpy((char *)linked_list->data + linked_list->len * linked_list->element_size, e,
         linked_list->element_size);
  linked_list->len++;
}

int vec_get(Vec *linked_list, size_t index, void *buffer) {
  if (0 <= index && index < linked_list->len) {
    void *data = (char *) linked_list->data + index * linked_list->element_size;
    memcpy(buffer, data, linked_list->element_size);
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

void vec_grow(Vec *linked_list) {
  // Calculate new capacity. The new capacity is the current capacity doubled.
  int new_capacity = linked_list->capacity * 2;
  if (new_capacity < MIN_CAPACITY)
    new_capacity = MIN_CAPACITY;

  // Allocate a new array with the new capacity
  void *array =
      realloc(linked_list->data, new_capacity * linked_list->element_size);
  // Failed to allocate memory, return.
  if (!array)
    return;

  linked_list->data = array;
  linked_list->capacity = new_capacity;
}

void vec_shrink(Vec *linked_list, size_t new_capacity) {
  if (new_capacity < linked_list->len)
    return;
  void *array =
      realloc(linked_list->data, new_capacity * linked_list->element_size);
  // Failed to allocate memory, return.
  if (!array)
    return;

  linked_list->data = array;
  linked_list->capacity = new_capacity;
}

void vec_clear(Vec *linked_list) {
  free(linked_list->data);
  linked_list->capacity = MIN_CAPACITY;
  linked_list->len = 0;
  void *array = calloc(linked_list->capacity, linked_list->element_size);
  // Failed to allocate memory, return.
  if (!array)
    return;
  linked_list->data = array;
}

size_t vec_len(Vec *linked_list) { return linked_list->len; }

bool vec_is_empty(Vec *linked_list) { return linked_list->len == 0; }
