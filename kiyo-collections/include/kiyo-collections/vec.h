#ifndef VEC_H
#define VEC_H

#include <stdbool.h>
#include <stddef.h>

/**
 * A contiguous growable array type, written as Vec, short for vector.
 */
typedef struct {
  /* Array which contains all stored elements. */
  void *data;
  /* Number of stored elements. */
  size_t len;
  /* How many elements fit inside data. */
  size_t capacity;
  /* Size of a single element. */
  size_t element_size;
} Vec;

/* Heap allocates a new vec. */
Vec *vec_new(size_t element_size);

/* Frees the vec and all stored elements. */
void vec_free(Vec *vec);

/**
 * Adds the element to the end of the vec.
 *
 * Time complexity: O(1)
 */
void vec_push(Vec *vec, void *e);

/**
 * If the index is outside of this vec, it will return EXIT FAILURE. Otherwise
 * adds the element to the specified index, shifting all elements after that
 * index one to the left. Then returns EXIT SUCCESS.
 *
 * Time complexity: O(n-i)
 */
int vec_insert(Vec *vec, size_t index, void *e);

/**
 * Copies all elements from the other vec to this vec. This will not change any
 * data inside the other vec.
 *
 * Time complexity: O(m)
 */
void vec_append(Vec *vec, Vec *other);

/**
 * If the index is outside of this vec, it will return EXIT FAILURE. Otherwise
 * removes the element at the given index, shiftig all elements after that index
 * one to the right. Then returns EXIT SUCCESS.
 *
 * Time complexity: O(n-i)
 */
int vec_remove(Vec *vec, size_t index, void *buffer);

/**
 * If the vec is empty, it will return EXIT FAILURE. Otherwise removes the last
 * element, writes it data to the buffer and returns EXIT SUCCESS.
 *
 * Time complexity: O(1)
 */
int vec_pop(Vec *vec, void *buffer);

/**
 * If the index is outside of this vec, it will return EXIT FAILURE. Otherwise
 * writes the data of the element of the specified index to the buffer, then
 * return EXIT SUCCESS.
 *
 * Time complexity: O(1)
 */
int vec_get(Vec *vec, size_t index, void *buffer);

/* Double the capacity, then reallocate data to the new capacity. */
void vec_grow(Vec *vec);

/* Returs if the new capacity is lower then the current len. Otherwise
 * reallocates data to the new capacity. */
void vec_shrink(Vec *vec, size_t new_capacity);

/* Returns the number of elements that are stored inside this vec. */
size_t vec_len(Vec *vec);

/* Returns the current capacity of data. The capacity reflects how many elements
 * can be stored inside data before new memory needs to be allocated. */
size_t vec_capacity(Vec *vec);

/* Returns if this vec does not contains any elements at all. */
bool vec_is_empty(Vec *vec);

/* Removes all elements that are inside this vec. */
void vec_clear(Vec *vec);

#endif
