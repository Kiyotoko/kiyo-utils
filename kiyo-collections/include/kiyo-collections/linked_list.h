#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "functions.h"
#include <stddef.h>
#include <stdlib.h>

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
 * Time complexity: O(min(i, n-i))
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
 * Time complexity: O(min(i, n-i))
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

#define GENERATE_LINKED_LIST_H(T) GENERATE_LINKED_LIST_NAMED_H(T, T)

#define GENERATE_LINKED_LIST_NAMED_H(N, T)                                     \
  typedef struct LinkedNode##N {                                               \
    T value;                                                                   \
    struct LinkedNode##N *prev;                                                \
    struct LinkedNode##N *next;                                                \
  } LinkedNode##N;                                                             \
  typedef struct {                                                             \
    LinkedNode##N *head;                                                       \
    LinkedNode##N *tail;                                                       \
    size_t len;                                                                \
  } LinkedList##N;                                                             \
  LinkedList##N *linked_list_##N##_new();                                      \
  void linked_list_##N##_free(LinkedList##N *linked_list);                     \
  bool linked_list_##N##_contains(LinkedList##N *linked_list,                  \
                                  Comperator comperator, T *value);            \
  void linked_list_##N##_push_front(LinkedList##N *linked_list, T value);      \
  void linked_list_##N##_push_back(LinkedList##N *linked_list, T value);       \
  int linked_list_##N##_front(LinkedList##N *linked_list, T *buffer);          \
  int linked_list_##N##_back(LinkedList##N *linked_list, T *buffer);           \
  int linked_list_##N##_get(LinkedList##N *linked_list, size_t index,          \
                            T *buffer);                                        \
  int linked_list_##N##_pop_front(LinkedList##N *linked_list, T *buffer);      \
  int linked_list_##N##_pop_back(LinkedList##N *linked_list, T *buffer);       \
  int linked_list_##N##_remove(LinkedList##N *linked_list, size_t index,       \
                               T *buffer);                                     \
  void linked_list_##N##_remove_if(LinkedList##N *linked_list, Test test);     \
  size_t linked_list_##N##_len(LinkedList##N *linked_list);                    \
  bool linked_list_##N##_is_empty(LinkedList##N *linked_list);                 \
  void linked_list_##N##_clear(LinkedList##N *linked_list);

#define GENERATE_LINKED_LIST_C(T) GENERATE_LINKED_LIST_NAMED_C(T, T)

#define GENERATE_LINKED_LIST_NAMED_C(N, T)                                     \
  LinkedNode##N *linked_node##N##_new(T value) {                               \
    LinkedNode##N *created = malloc(sizeof(LinkedNode##N));                    \
    if (!created)                                                              \
      return NULL;                                                             \
    created->value = value;                                                    \
    created->next = NULL;                                                      \
    created->prev = NULL;                                                      \
    return created;                                                            \
  }                                                                            \
  void linked_node##N##_free(LinkedNode##N *node) { free(node); }              \
  LinkedList##N *linked_list_##N##_new() {                                     \
    LinkedList##N *created = (LinkedList##N *)malloc(sizeof(LinkedList##N));   \
    if (!created)                                                              \
      return NULL;                                                             \
    created->head = NULL;                                                      \
    created->tail = NULL;                                                      \
    created->len = 0;                                                          \
    return created;                                                            \
  }                                                                            \
  void linked_list_##N##_free_data(LinkedList##N *linked_list) {               \
    LinkedNode##N *back = linked_list->tail;                                   \
    while (back) {                                                             \
      LinkedNode##N *current = back;                                           \
      back = current->prev;                                                    \
      linked_node##N##_free(current);                                          \
    }                                                                          \
  }                                                                            \
  void linked_list_##N##_free(LinkedList##N *linked_list) {                    \
    linked_list_##N##_free_data(linked_list);                                  \
    free(linked_list);                                                         \
  }                                                                            \
  bool linked_list_##N##_contains(LinkedList##N *linked_list,                  \
                                  Comperator comperator, T *value) {           \
    LinkedNode##N *element = linked_list->head;                                \
    while (element) {                                                          \
      if (!comperator(&(element->value), value)) {                             \
        return true;                                                           \
      }                                                                        \
      element = element->next;                                                 \
    }                                                                          \
    return false;                                                              \
  }                                                                            \
  void linked_list_##N##_push_front(LinkedList##N *linked_list, T value) {     \
    LinkedNode##N *created = linked_node##N##_new(value);                      \
    if (linked_list->head) {                                                   \
      created->next = linked_list->head;                                       \
      linked_list->head->prev = created;                                       \
    } else {                                                                   \
      linked_list->tail = created;                                             \
    }                                                                          \
    linked_list->head = created;                                               \
    linked_list->len++;                                                        \
  }                                                                            \
  void linked_list_##N##_push_back(LinkedList##N *linked_list, T value) {      \
    LinkedNode##N *created = linked_node##N##_new(value);                      \
    if (linked_list->head) {                                                   \
      linked_list->tail->next = created;                                       \
      created->prev = linked_list->tail;                                       \
    } else {                                                                   \
      linked_list->head = created;                                             \
    }                                                                          \
    linked_list->tail = created;                                               \
    linked_list->len++;                                                        \
  }                                                                            \
  int linked_list_##N##_front(LinkedList##N *linked_list, T *buffer) {         \
    if (linked_list->head) {                                                   \
      *buffer = linked_list->head->value;                                      \
      return EXIT_SUCCESS;                                                     \
    }                                                                          \
    return EXIT_FAILURE;                                                       \
  }                                                                            \
  int linked_list_##N##_back(LinkedList##N *linked_list, T *buffer) {          \
    if (linked_list->tail) {                                                   \
      *buffer = linked_list->tail->value;                                      \
      return EXIT_SUCCESS;                                                     \
    }                                                                          \
    return EXIT_FAILURE;                                                       \
  }                                                                            \
  LinkedNode##T *linked_list##T##_cursor(LinkedList##T *linked_list,           \
                                         size_t index) {                       \
    LinkedNode##T *node;                                                       \
    if (index < linked_list->len / 2) {                                        \
      node = linked_list->head;                                                \
      for (size_t i = 0; i < index; i++)                                       \
        node = node->next;                                                     \
    } else {                                                                   \
      node = linked_list->tail;                                                \
      for (size_t i = linked_list->len - 1; i > index; i--)                    \
        node = node->prev;                                                     \
    }                                                                          \
    return node;                                                               \
  }                                                                            \
  int linked_list_##N##_get(LinkedList##N *linked_list, size_t index,          \
                            T *buffer) {                                       \
    if (index < linked_list->len) {                                            \
      LinkedNode##N *p = linked_list##T##_cursor(linked_list, index);          \
      *buffer = p->value;                                                      \
      return EXIT_SUCCESS;                                                     \
    }                                                                          \
    return EXIT_FAILURE;                                                       \
  }                                                                            \
  int linked_list_##N##_pop_front(LinkedList##N *linked_list, T *buffer) {     \
    if (linked_list->head != NULL) {                                           \
      LinkedNode##N *head = linked_list->head;                                 \
      if (buffer)                                                              \
        *buffer = head->value;                                                 \
      if (head->next) {                                                        \
        head->next->prev = NULL;                                               \
      } else {                                                                 \
        linked_list->tail = NULL;                                              \
      }                                                                        \
      linked_list->head = head->next;                                          \
      linked_list->len--;                                                      \
      linked_node##N##_free(head);                                             \
      return EXIT_SUCCESS;                                                     \
    }                                                                          \
    return EXIT_FAILURE;                                                       \
  }                                                                            \
  int linked_list_##N##_pop_back(LinkedList##N *linked_list, T *buffer) {      \
    if (linked_list->tail != NULL) {                                           \
      LinkedNode##N *tail = linked_list->tail;                                 \
      if (buffer)                                                              \
        *buffer = tail->value;                                                 \
      if (tail->prev) {                                                        \
        tail->prev->next = NULL;                                               \
      } else {                                                                 \
        linked_list->head = NULL;                                              \
      }                                                                        \
      linked_list->tail = tail->prev;                                          \
      linked_list->len--;                                                      \
      linked_node##N##_free(tail);                                             \
      return EXIT_SUCCESS;                                                     \
    }                                                                          \
    return EXIT_FAILURE;                                                       \
  }                                                                            \
  void linked_list_##N##_relink(LinkedList##N *linked_list,                    \
                                LinkedNode##N *node) {                         \
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
  int linked_list_##N##_remove(LinkedList##N *linked_list, size_t index,       \
                               T *buffer) {                                    \
    if (index < linked_list->len) {                                            \
      LinkedNode##N *node = linked_list##T##_cursor(linked_list, index);       \
      if (buffer)                                                              \
        *buffer = node->value;                                                 \
      linked_list_##N##_relink(linked_list, node);                             \
      linked_list->len--;                                                      \
      linked_node##N##_free(node);                                             \
      return EXIT_SUCCESS;                                                     \
    }                                                                          \
    return EXIT_FAILURE;                                                       \
  }                                                                            \
  void linked_list_##N##_remove_if(LinkedList##N *linked_list, Test test) {    \
    LinkedNode##N *node = linked_list->head;                                   \
    while (node) {                                                             \
      LinkedNode##N *next = node->next;                                        \
      if (test(&(node->value))) {                                              \
        linked_list_##N##_relink(linked_list, node);                           \
        linked_list->len--;                                                    \
        linked_node##N##_free(node);                                           \
      }                                                                        \
      node = next;                                                             \
    }                                                                          \
  }                                                                            \
  size_t linked_list_##N##_len(LinkedList##N *linked_list) {                   \
    return linked_list->len;                                                   \
  }                                                                            \
  bool linked_list_##N##_is_empty(LinkedList##N *linked_list) {                \
    return linked_list->len == 0;                                              \
  }                                                                            \
  void linked_list_##N##_clear(LinkedList##N *linked_list) {                   \
    linked_list_##N##_free_data(linked_list);                                  \
    linked_list->head = NULL;                                                  \
    linked_list->tail = NULL;                                                  \
    linked_list->len = 0;                                                      \
  }

#endif
