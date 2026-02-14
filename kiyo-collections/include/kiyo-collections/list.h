#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include "functions.h"

/**
 * Two sided directional linked node.
 */
typedef struct BilinkedNode {
    void* value;
    struct BilinkedNode* prev;
    struct BilinkedNode* next;
} BilinkedNode;

/**
 * Implementation of the linked list with one directional
 * linking. Supports null values.
 */
typedef struct {
    BilinkedNode* head;
    BilinkedNode* tail;
    size_t len;
    size_t element_size;
} List;

/**
 * Creates and returns a new linked list without a head.
 */
List* list_create(size_t element_size);

/**
 * Destroys the linked list by freeing the memory of
 * the head if present and then itself.
 */
void list_destroy(List* list);

/**
 * Adds the value to the start of the linked list. This
 * will increase the len of the list and creates a new
 * node with the given value which then adds the node to
 * the start of the list.
 * 
 * Time complexity: O(1)
 */
void list_push(List* list, void* value);

/**
 * Adds the value to the end of the linked list. This
 * will increase the len of the list and creates a new
 * node with the given value which then adds the node to
 * the end of the list.
 * 
 * Time complexity: O(1)
 */
void list_add(List* list, void* value);

/**
 * Returns the first value of the list or null if this list
 * is empty.This is equal to calling the 'list_peek'
 * function.
 * 
 * Time complexity: O(1)
 */
int list_first(List* list, void* buffer);

/**
 * Returns the last value of the list or null if this
 * list is empty.
 * 
 * Time complexity: O(1)
 */
int list_last(List* list, void* buffer);

/**
 * Executes the given consumer for all elements in the list.
 * 
 * Time complexity: O(n)
 */
void list_foreach(List* list, Consumer consumer);

/**
 * Creates a new linked list from the given list and adds all
 * elements that statisfy the filter. This method will not
 * change the supplied list.
 * 
 * Time complexity: O(n)
 */
List* list_filter(List* list, Test test);

/**
 * Returns the value at the given index of the list. If the
 * index is out of bounds, then null will be returned. The
 * value may also be null if you added null values to the list.
 * 
 * Time complexity: O(n)
 */
int list_get(List* list, size_t index, void* buffer);

/**
 * Returns the first value of the list or null if this list
 * is empty.This is equal to calling the 'list_first'
 * function.
 * 
 * Time complexity: O(1)
 */
int list_peek(List* list, void* buffer);

/**
 * Returns and removes the first element of the list. If
 * the list is empty, it will return null instead.
 * 
 * Time complexity: O(1)
 */
int list_pop(List* list, void* buffer);

/**
 * Removes the element at the given index. Returns 0 on
 * success or 1 if it was index out of bounds.
 * 
 * Time complexity: O(n)
 */
int list_remove(List* list, size_t index, void* buffer);

int list_remove_obj(List* list, void* obj, size_t* buffer);

/**
 * Removes all elements of the list that statisfy the test.
 * 
 * Time complexity: O(n)
 */
void list_remove_if(List* list, Test test);

size_t list_len(List* list);

void list_clear(List* list);

/**
 * Creates a new iterator from the given list. You should
 * free the memory by calling the 'list_iter_destroy'
 * function.
 */
BilinkedNode** list_iter(List* list);

/**
 * Checks if there are any values left.
 */
bool list_iter_has_next(BilinkedNode** iter);

/**
 * Returns the current value and continue the iterator to
 * the next node. It should be always checked first if
 * there are any values left by checking the
 * 'list_iter_has_next' function. If this is not
 * done, then this may result in null pointer exceptions.
 */
void* list_iter_next(BilinkedNode** iter);

/**
 * Returns only the current value of the iterator. This
 * will not continue the iterator to the next node. If you
 * want to go to the next node, you should call
 * 'list_iter_next'.
 */
void* list_iter_peek(BilinkedNode** iter);

/**
 * Frees all allocated memory of the supplied iterator.
 * You should not call any methods of the iterator after
 * destroying it.
 */
void list_iter_destroy(BilinkedNode** iter);

#endif
