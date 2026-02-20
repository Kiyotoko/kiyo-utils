#ifndef LINKED_LIST_H
#define LINKED_LIST_H

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

#if ENABLE_GENERICS

#include <stdlib.h>
#include <string.h>

#define DECLARE_LINKED_LIST_H(T)                                               \
  typedef struct LinkedNode$##T {                                              \
    T value;                                                                   \
    struct LinkedNode$##T *prev;                                               \
    struct LinkedNode$##T *next;                                               \
  } LinkedNode$##T;                                                            \
  typedef struct {                                                             \
    LinkedNode$##T *head;                                                      \
    LinkedNode$##T *tail;                                                      \
    size_t len;                                                                \
  } LinkedList$##T;                                                            \
  LinkedList$##T *linked_list$##T##_new();                                     \
  void linked_list$##T##_free(LinkedList$##T *linked_list);                    \
  bool linked_list$##T##_contains(LinkedList$##T *linked_list,                 \
                                  Comperator comperator, T *value);

#define DECLARE_LINKED_LIST_C(T)                                               \
  LinkedNode$##T *linked_node$##T##_new(T element) {                           \
    LinkedNode$##T *created = malloc(sizeof(LinkedNode$##T));                  \
    if (!created) {                                                            \
      return NULL;                                                             \
    }                                                                          \
    /*memcpy(&(created->value), element, sizeof(T));*/                         \
    created->value = element;                                                  \
    created->next = NULL;                                                      \
    created->prev = NULL;                                                      \
    return created;                                                            \
  }                                                                            \
  void linked_node$##T##_free(LinkedNode$##T *node) { free(node); }            \
  LinkedList$##T *linked_list$##T##_new() {                                    \
    LinkedList$##T *created = (LinkedList$##T *)malloc(sizeof(LinkedList));    \
    if (!created)                                                              \
      return NULL;                                                             \
    created->head = NULL;                                                      \
    created->tail = NULL;                                                      \
    created->len = 0;                                                          \
    return created;                                                            \
  }                                                                            \
  void linked_list$##T##_free_data(LinkedList$##T *linked_list) {              \
    LinkedNode$##T *back = linked_list->tail;                                  \
    while (back) {                                                             \
      LinkedNode$##T *current = back;                                          \
      back = current->prev;                                                    \
      linked_node$##T##_free(current);                                         \
    }                                                                          \
  }                                                                            \
  void linked_list$##T##_free(LinkedList$##T *linked_list) {                   \
    linked_list$##T##_free_data(linked_list);                                  \
    free(linked_list);                                                         \
  }                                                                            \
  bool linked_list$##T##_contains(LinkedList$##T *linked_list,                 \
                                  Comperator comperator, T *value) {           \
    LinkedNode$##T *element = linked_list->head;                               \
    while (element) {                                                          \
      if (!comperator(&(element->value), value)) {                             \
        return true;                                                           \
      }                                                                        \
      element = element->next;                                                 \
    }                                                                          \
    return false;                                                              \
  }                                                                            \
  void linked_list$##T##_push_front(LinkedList$##T *linked_list, T value) {    \
    LinkedNode$##T *created = linked_node$##T##_new(value);                    \
    if (linked_list->head) {                                                   \
      created->next = linked_list->head;                                       \
      linked_list->head->prev = created;                                       \
    } else {                                                                   \
      linked_list->tail = created;                                             \
    }                                                                          \
    linked_list->head = created;                                               \
    linked_list->len++;                                                        \
  }                                                                            \
  void linked_list$##T##_push_back(LinkedList$##T *linked_list, T value) {     \
    LinkedNode$##T *created = linked_node$##T##_new(value);                    \
    if (linked_list->head) {                                                   \
      linked_list->tail->next = created;                                       \
      created->prev = linked_list->tail;                                       \
    } else {                                                                   \
      linked_list->head = created;                                             \
    }                                                                          \
    linked_list->tail = created;                                               \
    linked_list->len++;                                                        \
  }                                                                            \
  int linked_list$##T##_front(LinkedList$##T *linked_list, T *buffer) {        \
    if (linked_list->head) {                                                   \
      *buffer = linked_list->head->value;                                      \
      return EXIT_SUCCESS;                                                     \
    }                                                                          \
    return EXIT_FAILURE;                                                       \
  }                                                                            \
  int linked_list$##T##_back(LinkedList$##T *linked_list, T *buffer) {         \
    if (linked_list->tail) {                                                   \
      *buffer = linked_list->tail->value;                                      \
      return EXIT_SUCCESS;                                                     \
    }                                                                          \
    return EXIT_FAILURE;                                                       \
  }                                                                            \
  int linked_list$##T##_get(LinkedList$##T *linked_list, size_t index,         \
                            T *buffer) {                                       \
    if (index < linked_list->len) {                                            \
      LinkedNode$##T *p = linked_list->head;                                   \
      for (size_t i = 0; i < index; i++) {                                     \
        p = p->next;                                                           \
      }                                                                        \
      *buffer = p->value;                                                      \
      return EXIT_SUCCESS;                                                     \
    }                                                                          \
    return EXIT_FAILURE;                                                       \
  }                                                                            \
  int linked_list$##T##_pop_front(LinkedList$##T *linked_list, T *buffer) {    \
    if (linked_list->head != NULL) {                                           \
      LinkedNode$##T *head = linked_list->head;                                \
      if (buffer)                                                              \
        *buffer = head->value;                                                 \
      if (head->next) {                                                        \
        head->next->prev = NULL;                                               \
      } else {                                                                 \
        linked_list->tail = NULL;                                              \
      }                                                                        \
      linked_list->head = head->next;                                          \
      linked_list->len--;                                                      \
      linked_node$##T##_free(head);                                            \
      return EXIT_SUCCESS;                                                     \
    }                                                                          \
    return EXIT_FAILURE;                                                       \
  }                                                                            \
  int linked_list$##T##_pop_back(LinkedList$##T *linked_list, T *buffer) {     \
    if (linked_list->tail != NULL) {                                           \
      LinkedNode$##T *tail = linked_list->tail;                                \
      if (buffer)                                                              \
        *buffer = tail->value;                                                 \
      if (tail->prev) {                                                        \
        tail->prev->next = NULL;                                               \
      } else {                                                                 \
        linked_list->head = NULL;                                              \
      }                                                                        \
      linked_list->tail = tail->prev;                                          \
      linked_list->len--;                                                      \
      linked_node$##T##_free(tail);                                            \
      return EXIT_SUCCESS;                                                     \
    }                                                                          \
    return EXIT_FAILURE;                                                       \
  }                                                                            \
  void linked_list$##T##_relink(LinkedList$##T *linked_list,                   \
                                LinkedNode$##T *node) {                        \
    if (node->prev) {                                                          \
      node->prev->next = node->next;                                           \
    } else {                                                                   \
      linked_list->head = node->next;                                          \
    }                                                                          \
    if (node->next) {                                                          \
      node->next->prev = node->prev;                                           \
    } else {                                                                   \
      linked_list->tail = node->prev;                                          \
    }                                                                          \
  }                                                                            \
  int linked_list$##T##_remove(LinkedList$##T *linked_list, size_t index,      \
                               T *buffer) {                                    \
    if (index < linked_list->len) {                                            \
      LinkedNode$##T *node = linked_list->head;                                \
      for (size_t i = 0; i < index; i++) {                                     \
        node = node->next;                                                     \
      }                                                                        \
      if (buffer)                                                              \
        *buffer = node->value;                                                 \
      linked_list$##T##_relink(linked_list, node);                             \
      linked_list->len--;                                                      \
      linked_node$##T##_free(node);                                            \
      return EXIT_SUCCESS;                                                     \
    }                                                                          \
    return EXIT_FAILURE;                                                       \
  }                                                                            \
  void linked_list$##T##_remove_if(LinkedList$##T *linked_list, Test test) {   \
    LinkedNode$##T *node = linked_list->head;                                  \
    while (node) {                                                             \
      LinkedNode$##T *next = node->next;                                       \
      if (test(&(node->value))) {                                              \
        linked_list$##T##_relink(linked_list, node);                           \
        linked_list->len--;                                                    \
        linked_node$##T##_free(node);                                          \
      }                                                                        \
      node = next;                                                             \
    }                                                                          \
  }                                                                            \
  size_t linked_list$##T##_len(LinkedList$##T *linked_list) {                  \
    return linked_list->len;                                                   \
  }                                                                            \
  bool linked_list$##T##_is_empty(LinkedList$##T *linked_list) {               \
    return linked_list->len == 0;                                              \
  }                                                                            \
  void linked_list$##T##_clear(LinkedList$##T *linked_list) {                  \
    linked_list$##T##_free_data(linked_list);                                  \
    linked_list->head = NULL;                                                  \
    linked_list->tail = NULL;                                                  \
    linked_list->len = 0;                                                      \
  }

#endif

#endif
