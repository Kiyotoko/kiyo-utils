#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>
#include "functions.h"

/**
 * One directional linked node.
 */
typedef struct LinkedNode {
    void* value;
    struct LinkedNode* next;    
} LinkedNode;

/**
 * Implementation of the linked list with one directional
 * linking. Supports null values.
 */
typedef struct {
    LinkedNode* head;
    LinkedNode* tail;
    size_t len;
    size_t element_size;
} LinkedList;

/**
 * Creates and returns a new linked list without a head.
 */
LinkedList* linked_list_create(size_t element_size);

/**
 * Destroys the linked list by freeing the memory of
 * the head if present and then itself.
 */
void linked_list_destroy(LinkedList* list);

/**
 * Adds the value to the start of the linked list. This
 * will increase the len of the list and creates a new
 * node with the given value which then adds the node to
 * the start of the list.
 * 
 * Time complexity: O(1)
 */
void linked_list_push(LinkedList* list, void* value);

/**
 * Adds the value to the end of the linked list. This
 * will increase the len of the list and creates a new
 * node with the given value which then adds the node to
 * the end of the list.
 * 
 * Time complexity: O(1)
 */
void linked_list_add(LinkedList* list, void* value);

/**
 * Returns the first value of the list or null if this list
 * is empty.This is equal to calling the 'linked_list_peek'
 * function.
 * 
 * Time complexity: O(1)
 */
void* linked_list_first(LinkedList* list);

/**
 * Returns the last value of the list or null if this
 * list is empty.
 * 
 * Time complexity: O(1)
 */
void* linked_list_last(LinkedList* list);

/**
 * Executes the given consumer for all elements in the list.
 * 
 * Time complexity: O(n)
 */
void linked_list_foreach(LinkedList* list, Consumer consumer);

/**
 * Creates a new linked list from the given list and adds all
 * elements that statisfy the filter. This method will not
 * change the supplied list.
 * 
 * Time complexity: O(n)
 */
LinkedList* linked_list_filter(LinkedList* list, Test test);

/**
 * Returns the value at the given index of the list. If the
 * index is out of bounds, then null will be returned. The
 * value may also be null if you added null values to the list.
 * 
 * Time complexity: O(n)
 */
void* linked_list_get(LinkedList* list, size_t index);

/**
 * Returns the first value of the list or null if this list
 * is empty.This is equal to calling the 'linked_list_first'
 * function.
 * 
 * Time complexity: O(1)
 */
void* linked_list_peek(LinkedList* list);

/**
 * Returns and removes the first element of the list. If
 * the list is empty, it will return null instead.
 * 
 * Time complexity: O(1)
 */
void* linked_list_pop(LinkedList* list);

/**
 * Removes the element at the given index. Returns true on
 * success or false if it was index out of bounds.
 * 
 * Time complexity: O(n)
 */
bool linked_list_remove(LinkedList* list, size_t index);

/**
 * Removes all elements of the list that statisfy the test.
 * 
 * Time complexity: O(n)
 */
void linked_list_remove_if(LinkedList* list, Test test);

/**
 * Creates a new iterator from the given list.
 */
LinkedNode** linked_list_iter(LinkedList* list);

/**
 * Checks if there are any values left.
 */
bool linked_list_iter_has_next(LinkedNode** iter);

/**
 * Returns the current value and continue the iterator to
 * the next node. It should be always checked first if
 * there are any values left by checking the
 * 'linked_list_iter_has_next' function. If this is not
 * done, then this may result in null pointer exceptions.
 */
void* linked_list_iter_next(LinkedNode** iter);

/**
 * Returns only the current value of the iterator. This
 * will not continue the iterator to the next node. If you
 * want to go to the next node, you should call
 * 'linked_list_iter_next'.
 */
void* linked_list_iter_peek(LinkedNode** iter);

#endif
