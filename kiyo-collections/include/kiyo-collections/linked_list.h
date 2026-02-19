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
 * Implementation of the linked list with bidirectional linking. If the linked
 * list is empty, both head and tail are NULL. If the linked list contains
 * exactly one element, the head and tail should point to the same element. The
 * element size should not be changed after a linked list was created. Changing
 * its value may result in segvault.
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
 * Returns if the linked list contains a element that is equal to the given
 * value based on the comperator.
 *
 * Time complexity: O(n)
 */
bool linked_list_contains(LinkedList *linked_list, Comperator comperator,
                          void *value);

/**
 * Adds the value to the start of the linked list. This will increase the len of
 * the linked list and creates a new node with the given value which then adds
 * the node to the start of the linked list.
 *
 * Time complexity: O(1)
 */
void linked_list_push_front(LinkedList *linked_list, void *value);

/**
 * Adds the value to the end of the linked list. This will increase the len of
 * the linked list and creates a new node with the given value which then adds
 * the node to the end of the linked list.
 *
 * Time complexity: O(1)
 */
void linked_list_push_back(LinkedList *linked_list, void *value);

/**
 * If the linked list is empty, returns EXIT FAILURE. Otherwise writes the
 * content of the first element to the buffer and returns EXIT SUCCESS.
 *
 * Time complexity: O(1)
 */
int linked_list_front(LinkedList *linked_list, void *buffer);

/**
 * If the linked list is empty, returns EXIT FAILURE. Otherwise writes the
 * content of the last element to the buffer and returns EXIT SUCCESS.
 *
 * Time complexity: O(1)
 */
int linked_list_back(LinkedList *linked_list, void *buffer);

/**
 * If the index does not point to a valid element, return EXIT FAILURE.
 * Otherwise writes the content of the element to the buffer and returns EXIT
 * SUCCESS.
 *
 * Time complexity: O(n)
 */
int linked_list_get(LinkedList *linked_list, size_t index, void *buffer);

/**
 * If the linked list is empty, return EXIT FAILURE. Otherwise write the content
 * of the first element to the buffer, remove it and return EXIT SUCCESS.
 *
 * Time complexity: O(1)
 */
int linked_list_pop_front(LinkedList *linked_list, void *buffer);

/**
 * If the linked list is empty, return EXIT FAILURE. Otherwise write the content
 * of the last element to the buffer, remove it and return EXIT SUCCESS.
 *
 * Time complexity: O(1)
 */
int linked_list_pop_back(LinkedList *linked_list, void *buffer);

/**
 * Removes the element at the given index. Returns EXIT FAILURE if the index was
 * out of bounds, EXIT SUCCESS otherwise.
 *
 * Time complexity: O(n)
 */
int linked_list_remove(LinkedList *linked_list, size_t index, void *buffer);

/**
 * Removes all elements of the linked list that statisfy the test. A element is
 * removed if the test returns true.
 *
 * Time complexity: O(n)
 */
void linked_list_remove_if(LinkedList *linked_list, Test test);

/**
 * Returns the number of the elements that are inside the linked list.
 *
 * Time complexity: O(1)
 */
size_t linked_list_len(LinkedList *linked_list);

/**
 * Returns if the linked list is empty or not.
 *
 * Time complexity: O(1)
 */
bool linked_list_is_empty(LinkedList *linked_list);

/**
 * Removes all elements of the linked list and free all heap allocated memory.
 * Sets the len of the linked list to 0.
 *
 * Time complexity: O(n)
 */
void linked_list_clear(LinkedList *linked_list);

#endif
