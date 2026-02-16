#include <stdlib.h>
#include <string.h>
#include "kiyo-collections/linked_list.h"

LinkedNode* linked_node_new(void* element, size_t element_size) {
    // Allocate a new node that we later add to the linked_list first.
    LinkedNode* created = calloc(1, sizeof(LinkedNode));
    if (!created) {
        return false;
    }
    created->value = malloc(element_size);
    created->next = NULL;
    created->prev = NULL;
    if (element != NULL) {
        memcpy(created->value, element, element_size);
    }

    return created;
}

void linked_node_free(LinkedNode* node) {
    if (node->value) {
        free(node->value);
    }
    free(node);
}

void linked_node_free_recursive(LinkedNode* node) {
    if (node->next) {
        linked_node_free_recursive(node->next);
    }
    linked_node_free(node);
}

LinkedList* linked_list_new(size_t element_size) {
    LinkedList* created = (LinkedList*) calloc(1, sizeof(LinkedList));
    if (!created) return NULL;
    created->element_size = element_size;

    return created;
}

void linked_list_free(LinkedList* linked_list) {
    if (linked_list->head != NULL) {
        linked_node_free_recursive(linked_list->head);
    }
    free(linked_list);
}

void linked_list_push(LinkedList* linked_list, void* value) {
    LinkedNode* created = linked_node_new(value, linked_list->element_size);
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

void linked_list_add(LinkedList* linked_list, void* value) {
    LinkedNode* created = linked_node_new(value, linked_list->element_size);
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

int linked_list_first(LinkedList* linked_list, void* buffer) {
    if (linked_list->head) {
        memcpy(buffer, linked_list->head->value, linked_list->element_size);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int linked_list_last(LinkedList* linked_list, void* buffer) {
    if (linked_list->tail) {
        memcpy(buffer, linked_list->tail->value, linked_list->element_size);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int linked_list_get(LinkedList* linked_list, size_t index, void* buffer) {
    // Check for index out of bounds.
    if (0 <= index && index < linked_list->len) {
        LinkedNode* p = linked_list->head;
        for (size_t i = 0; i < index; i++) {
            p = p->next;
        }
        memcpy(buffer, p->value, linked_list->element_size);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int linked_list_peek(LinkedList* linked_list, void* buffer) {
    return linked_list_first(linked_list, buffer);
}

int linked_list_pop(LinkedList* linked_list, void* buffer) {
    if (linked_list->head != NULL) {
        LinkedNode* head = linked_list->head;
        if (buffer) memcpy(buffer, head->value, linked_list->element_size);
        head->next->prev = NULL;
        linked_list->head = head->next;
        linked_list->len--;
        linked_node_free(head);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

void linked_list_relink(LinkedList* linked_list, LinkedNode* node) {
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

int linked_list_remove(LinkedList* linked_list, size_t index, void* buffer) {
    if (0 <= index && index < linked_list->len) {
        // Loop througt the linked_list starting at the head to find the node at
        // the given index.
        LinkedNode* node = linked_list->head;
        for (size_t i = 0; i < index; i++) {
            node = node->next;
        }

        if (buffer) memcpy(buffer, node->value, linked_list->element_size);
        linked_list_relink(linked_list, node);

        linked_list->len--;
        linked_node_free(node);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int linked_list_remove_obj(LinkedList* linked_list, void* obj, size_t* buffer) {
    size_t i = 0;
    for (LinkedNode* node = linked_list->head; node; node = node->next) {
        if (!memcmp(node->value, obj, linked_list->element_size)) {
            memcpy(buffer, &i, sizeof(size_t));
            linked_list_relink(linked_list, node);

            // Decrease len of the linked_list.
            linked_list->len--;
            // Free allocated memory.
            linked_node_free(node);
            return EXIT_SUCCESS;
        }
        i++;
    }
    return EXIT_FAILURE;
}

void linked_list_remove_if(LinkedList* linked_list, Test test) {
    for (LinkedNode* node = linked_list->head; node; node = node->next) {
        if (test(node->value)) {
            linked_list_relink(linked_list, node);

            // Decrease len of the linked_list.
            linked_list->len--;
            // Free allocated memory.
            linked_node_free(node);
        }
    }
}

size_t linked_list_len(LinkedList* linked_list) {
    return linked_list->len;
}

void linked_list_clear(LinkedList* linked_list) {
    if (linked_list->head) {
        linked_node_free_recursive(linked_list->head);
    }
    linked_list->len = 0;
}

LinkedNode** linked_list_iter(LinkedList* linked_list) {
    return &(linked_list->head);
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
