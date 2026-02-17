#ifndef LIST_H
#define LIST_H

#include "functions.h"
#include <stddef.h>

/**
 * Two sided directional linked node.
 */
typedef struct LinkedNode {
  void *value;
  struct LinkedNode *prev;
  struct LinkedNode *next;
} LinkedNode;

/**
 * Implementation of the linked list with one directional
 * linking. Supports null values.
 */
typedef struct {
  LinkedNode *head;
  LinkedNode *tail;
  size_t len;
  size_t element_size;
} LinkedList;

/**
 * Creates and returns a new linked list without a head.
 */
LinkedList *linked_list_new(size_t element_size);

/**
 * Destroys the linked list by freeing the memory of
 * the head if present and then itself.
 */
void linked_list_free(LinkedList *linked_list);

/**
 * Adds the value to the start of the linked list. This
 * will increase the len of the linked_list and creates a new
 * node with the given value which then adds the node to
 * the start of the linked_list.
 *
 * Time complexity: O(1)
 */
void linked_list_push(LinkedList *linked_list, void *value);

/**
 * Adds the value to the end of the linked list. This
 * will increase the len of the linked_list and creates a new
 * node with the given value which then adds the node to
 * the end of the linked_list.
 *
 * Time complexity: O(1)
 */
void linked_list_add(LinkedList *linked_list, void *value);

/**
 * Returns the first value of the linked_list or null if this linked_list
 * is empty.This is equal to calling the 'linked_list_peek'
 * function.
 *
 * Time complexity: O(1)
 */
int linked_list_first(LinkedList *linked_list, void *buffer);

/**
 * Returns the last value of the linked_list or null if this
 * linked_list is empty.
 *
 * Time complexity: O(1)
 */
int linked_list_last(LinkedList *linked_list, void *buffer);

/**
 * Returns the value at the given index of the linked_list. If the
 * index is out of bounds, then null will be returned. The
 * value may also be null if you added null values to the linked_list.
 *
 * Time complexity: O(n)
 */
int linked_list_get(LinkedList *linked_list, size_t index, void *buffer);

/**
 * Returns the first value of the linked_list or null if this linked_list
 * is empty.This is equal to calling the 'linked_list_first'
 * function.
 *
 * Time complexity: O(1)
 */
int linked_list_peek(LinkedList *linked_list, void *buffer);

/**
 * Returns and removes the first element of the linked_list. If
 * the linked_list is empty, it will return null instead.
 *
 * Time complexity: O(1)
 */
int linked_list_pop(LinkedList *linked_list, void *buffer);

/**
 * Removes the element at the given index. Returns 0 on
 * success or 1 if it was index out of bounds.
 *
 * Time complexity: O(n)
 */
int linked_list_remove(LinkedList *linked_list, size_t index, void *buffer);

int linked_list_remove_obj(LinkedList *linked_list, void *obj, size_t *buffer);

/**
 * Removes all elements of the linked_list that statisfy the test.
 *
 * Time complexity: O(n)
 */
void linked_list_remove_if(LinkedList *linked_list, Test test);

size_t linked_list_len(LinkedList *linked_list);

void linked_list_clear(LinkedList *linked_list);

/**
 * Creates a new iterator from the given linked_list. You should
 * free the memory by calling the 'linked_list_iter_free'
 * function.
 */
LinkedNode **linked_list_iter(LinkedList *linked_list);

/**
 * Checks if there are any values left.
 */
bool linked_list_iter_has_next(LinkedNode **iter);

/**
 * Returns the current value and continue the iterator to
 * the next node. It should be always checked first if
 * there are any values left by checking the
 * 'linked_list_iter_has_next' function. If this is not
 * done, then this may result in null pointer exceptions.
 */
void *linked_list_iter_next(LinkedNode **iter);

/**
 * Returns only the current value of the iterator. This
 * will not continue the iterator to the next node. If you
 * want to go to the next node, you should call
 * 'linked_list_iter_next'.
 */
void *linked_list_iter_peek(LinkedNode **iter);

/**
 * Frees all allocated memory of the supplied iterator.
 * You should not call any methods of the iterator after
 * destroying it.
 */
void linked_list_iter_free(LinkedNode **iter);

#endif
