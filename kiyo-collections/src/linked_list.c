#include <stdlib.h>
#include <string.h>
#include "kiyo-collections/linked_list.h"

LinkedNode* linked_node_create(void* element, size_t element_size) {
    // Allocate a new node that we later add to the list first.
    LinkedNode* created = calloc(1, sizeof(LinkedNode));
    if (!created) {
        return false;
    }
    created->value = malloc(element_size);
    created->next = NULL;
    if (element != NULL) {
        memcpy(created->value, element, element_size);
    }

    return created;
}

void linked_node_destroy(LinkedNode* node) {
    if (node->value) {
        free(node->value);
    }
    free(node);
}

void linked_node_destroy_recursive(LinkedNode* node) {
    if (node->next) {
        linked_node_destroy_recursive(node->next);
    }
    linked_node_destroy(node);
}

LinkedList* linked_list_create(size_t element_size) {
    LinkedList* created = (LinkedList*) calloc(1, sizeof(LinkedList));
    if (!created) return NULL;
    created->element_size = element_size;

    return created;
}

void linked_list_destroy(LinkedList* list) {
    if (list->head != NULL) {
        linked_node_destroy_recursive(list->head);
    }
    free(list);
}

void linked_list_push(LinkedList* list, void* value) {
    LinkedNode* created = linked_node_create(value, list->element_size);
    if (list->head) {
        created->next = list->head;
    } else {
        list->tail = created;
    }
    list->head = created;
    // Increase the size of the list;
    list->len++;
}

void linked_list_add(LinkedList* list, void* value) {
    LinkedNode* created = linked_node_create(value, list->element_size);
    if (list->head) {
        list->tail->next = created;
    } else {
        list->head = created;
    }
    list->tail = created;
    // Increase the size of the list;
    list->len++;
}

void* linked_list_first(LinkedList* list) {
    return (list->head) ? list->head->value : NULL;
}

void* linked_list_last(LinkedList* list) {
    return (list->tail) ? list->tail->value : NULL;
}

void* linked_list_get(LinkedList* list, size_t index) {
    // Check for index out of bounds.
    if (index >= list->len) return false;

    LinkedNode* p = list->head;
    for (size_t i = 0; i < index; i++) {
        p = p->next;
    }
    return p->value;
}

void linked_list_foreach(LinkedList* list, Consumer consumer) {
    LinkedNode* p = list->head;
    if (p) {
        while (p->next) {
            consumer(p->value);
            p = p->next;
        }
        consumer(p->value);
    }
}

LinkedList* linked_list_filter(LinkedList* list, Test test) {
    LinkedNode* node = list->head;
    LinkedList* created = linked_list_create(list->element_size);
    while (node) {
        if (test(node)) linked_list_add(created, node->value);
        node = node->next;
    }
    return created;
}

void* linked_list_peek(LinkedList* list) {
    if (list->head != NULL) {
        return list->head->value;
    }
    return NULL;
}

void* linked_list_pop(LinkedList* list) {
    if (list->head != NULL) {
        LinkedNode* head = list->head;
        void* previous = head->value;
        list->head = head->next;
        list->len--;
        linked_node_destroy(head);
        return previous;
    }
    return NULL;
}

bool linked_list_remove(LinkedList* list, size_t index) {
    if (index >= list->len)
        // We return here because the index is out of bounds.
        return false;
    else if (index == 0) {
        // Remove the head of the list.
        linked_list_pop(list);
    } else if (list->head != NULL) {
        // Loop througt the list starting at the head to find the node at
        // the given index.
        LinkedNode* p = list->head;
        for (size_t i = 1; i < index; i++) {
            p = p->next;
        }

        // Cache the deleted note so that we can later free it.
        LinkedNode* deleted = p->next;

        if (index == list->len -1) {
            // Remove the tail of the list.
            list->tail = p;
            p->next = NULL;
        } else {
            p->next = deleted->next;
        }
        list->len--;
        linked_node_destroy(deleted);
    }
    return true;
}

void linked_list_remove_if(LinkedList* list, Test test) {
    LinkedNode* previous = NULL;
    LinkedNode* node = list->head;
    while (node) {
        LinkedNode* next = node->next;
        if (test(node->value)) {
            // Check if removed element was head or tail.
            if (node == list->head) {
                list->head = node->next;
            }
            if (node == list->tail) {
                list->tail = previous;
            }
            // Change linking.
            if (previous) {
                previous->next = node->next;
            }
            // Decrease len of the list.
            list->len--;
            // Free allocated memory.
            linked_node_destroy(node);
        } else {
            previous = node;
        }
        node = next;
    }
}

LinkedNode** linked_list_iter(LinkedList* list) {
    return &(list->head);
}

bool linked_list_iter_has_next(LinkedNode** iter) {
    return *iter != NULL;
}

void* linked_list_iter_next(LinkedNode** iter) {
    void* value = (*iter)->value;
    *iter = (*iter)->next;
    return value;
}

void* linked_list_iter_peek(LinkedNode** iter) {
    return (*iter)->value;
}
