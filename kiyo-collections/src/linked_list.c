#include "kiyo-collections/linked_list.h"
#include "kiyo-collections/functions.h"
#include <stdlib.h>
#include <string.h>

LinkedNode *linked_node_new(void *element, size_t element_size) {
  // Allocate a new node that we later add to the linked_list first.
  LinkedNode *created = malloc(sizeof(LinkedNode));
  if (!created) {
    return NULL;
  }

  created->value = malloc(element_size);
  if (!created->value) {
    free(created);
    return NULL;
  }
  memcpy(created->value, element, element_size);

  created->next = NULL;
  created->prev = NULL;

  return created;
}

void linked_node_free(LinkedNode *node) {
  free(node->value);
  free(node);
}

LinkedList *linked_list_new(size_t element_size) {
  LinkedList *created = (LinkedList *)malloc(sizeof(LinkedList));
  if (!created)
    return NULL;
  created->head = NULL;
  created->tail = NULL;
  created->len = 0;
  created->element_size = element_size;

  return created;
}

void linked_list_free_data(LinkedList *linked_list) {
  LinkedNode *back = linked_list->tail;
  while (back) {
    LinkedNode *current = back;
    back = current->prev;
    linked_node_free(current);
  }
}

void linked_list_free(LinkedList *linked_list) {
  linked_list_free_data(linked_list);
  free(linked_list);
}

bool linked_list_contains(LinkedList *linked_list, Comperator comperator,
                          void *value) {
  LinkedNode *element = linked_list->head;
  while (element) {
    if (!comperator(element->value, value)) {
      return true;
    }
    element = element->next;
  }
  return false;
}

void linked_list_push_front(LinkedList *linked_list, void *value) {
  LinkedNode *created = linked_node_new(value, linked_list->element_size);
  if (linked_list->head) {
    created->next = linked_list->head;
    linked_list->head->prev = created;
  } else {
    linked_list->tail = created;
  }
  linked_list->head = created;
  // Increase the size of the linked_list;
  linked_list->len++;
}

void linked_list_push_back(LinkedList *linked_list, void *value) {
  LinkedNode *created = linked_node_new(value, linked_list->element_size);
  if (linked_list->head) {
    linked_list->tail->next = created;
    created->prev = linked_list->tail;
  } else {
    linked_list->head = created;
  }
  linked_list->tail = created;
  // Increase the size of the linked_list;
  linked_list->len++;
}

int linked_list_front(LinkedList *linked_list, void *buffer) {
  if (linked_list->head) {
    memcpy(buffer, linked_list->head->value, linked_list->element_size);
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int linked_list_back(LinkedList *linked_list, void *buffer) {
  if (linked_list->tail) {
    memcpy(buffer, linked_list->tail->value, linked_list->element_size);
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int linked_list_get(LinkedList *linked_list, size_t index, void *buffer) {
  // Check for index out of bounds.
  if (index < linked_list->len) {
    LinkedNode *p = linked_list->head;
    for (size_t i = 0; i < index; i++) {
      p = p->next;
    }
    memcpy(buffer, p->value, linked_list->element_size);
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int linked_list_pop_front(LinkedList *linked_list, void *buffer) {
  if (linked_list->head != NULL) {
    LinkedNode *head = linked_list->head;
    if (buffer)
      memcpy(buffer, head->value, linked_list->element_size);
    if (head->next) {
      head->next->prev = NULL;
    } else {
      linked_list->tail = NULL;
    }
    linked_list->head = head->next;
    linked_list->len--;
    linked_node_free(head);
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int linked_list_pop_back(LinkedList *linked_list, void *buffer) {
  if (linked_list->tail != NULL) {
    LinkedNode *tail = linked_list->tail;
    if (buffer)
      memcpy(buffer, tail->value, linked_list->element_size);
    if (tail->prev) { // There is at least one other element
      tail->prev->next = NULL;
    } else { // The list is now empty, set the head to null
      linked_list->head = NULL;
    }
    linked_list->tail = tail->prev;
    linked_list->len--;
    linked_node_free(tail);
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

void linked_list_relink(LinkedList *linked_list, LinkedNode *node) {
  // Change linking
  if (node->prev) {
    // Previous element exists
    node->prev->next = node->next;
  } else {
    // Node is head
    linked_list->head = node->next;
  }
  if (node->next) {
    // Next element exists
    node->next->prev = node->prev;
  } else {
    // Node is tail
    linked_list->tail = node->prev;
  }
}

int linked_list_remove(LinkedList *linked_list, size_t index, void *buffer) {
  if (index < linked_list->len) {
    // Loop througt the linked list starting at the head to find the node at
    // the given index.
    LinkedNode *node = linked_list->head;
    for (size_t i = 0; i < index; i++) {
      node = node->next;
    }

    if (buffer)
      memcpy(buffer, node->value, linked_list->element_size);
    linked_list_relink(linked_list, node);

    linked_list->len--;
    linked_node_free(node);
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

void linked_list_remove_if(LinkedList *linked_list, Test test) {
  LinkedNode *node = linked_list->head;
  while (node) {
    // Store next node before it may be freed.
    LinkedNode *next = node->next;
    if (test(node->value)) {
      // Currently the list is structured as a -> b -> c and
      // we remove b here. Therefore we directly connect a with c.
      linked_list_relink(linked_list, node);

      // Decrease len of the linked_list.
      linked_list->len--;
      // Free allocated memory.
      linked_node_free(node);
    }
    node = next;
  }
}

size_t linked_list_len(LinkedList *linked_list) { return linked_list->len; }

bool linked_list_is_empty(LinkedList *linked_list) {
  return linked_list->len == 0;
}

void linked_list_clear(LinkedList *linked_list) {
  linked_list_free_data(linked_list);
  linked_list->head = NULL;
  linked_list->tail = NULL;
  linked_list->len = 0;
}
