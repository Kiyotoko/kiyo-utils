#include <stdlib.h>
#include <string.h>
#include "kiyo-collections/list.h"

BilinkedNode* bilinked_node_create(void* element, size_t element_size) {
    // Allocate a new node that we later add to the list first.
    BilinkedNode* created = calloc(1, sizeof(BilinkedNode));
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

void bilinked_node_destroy(BilinkedNode* node) {
    if (node->value) {
        free(node->value);
    }
    free(node);
}

void bilinked_node_destroy_recursive(BilinkedNode* node) {
    if (node->next) {
        bilinked_node_destroy_recursive(node->next);
    }
    bilinked_node_destroy(node);
}

List* list_create(size_t element_size) {
    List* created = (List*) calloc(1, sizeof(List));
    if (!created) return NULL;
    created->element_size = element_size;

    return created;
}

void list_destroy(List* list) {
    if (list->head != NULL) {
        bilinked_node_destroy_recursive(list->head);
    }
    free(list);
}

void list_push(List* list, void* value) {
    BilinkedNode* created = bilinked_node_create(value, list->element_size);
    if (list->head) {
        created->next = list->head;
        list->head->prev = created;
    } else {
        list->tail = created;
    }
    list->head = created;
    // Increase the size of the list;
    list->len++;
}

void list_add(List* list, void* value) {
    BilinkedNode* created = bilinked_node_create(value, list->element_size);
    if (list->head) {
        list->tail->next = created;
        created->prev = list->tail;
    } else {
        list->head = created;
    }
    list->tail = created;
    // Increase the size of the list;
    list->len++;
}

int list_first(List* list, void* buffer) {
    if (list->head) {
        memcpy(buffer, list->head->value, list->element_size);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int list_last(List* list, void* buffer) {
    if (list->tail) {
        memcpy(buffer, list->tail->value, list->element_size);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int list_get(List* list, size_t index, void* buffer) {
    // Check for index out of bounds.
    if (0 <= index && index < list->len) {
        BilinkedNode* p = list->head;
        for (size_t i = 0; i < index; i++) {
            p = p->next;
        }
        memcpy(buffer, p->value, list->element_size);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

void list_foreach(List* list, Consumer consumer) {
    BilinkedNode* p = list->head;
    // Check if list is empty
    if (p) {
        // Apply consumer to all values
        consumer(p->value);
        while (p->next) {
            consumer(p->value);
            p = p->next;
        }
    }
}

List* list_filter(List* list, Test test) {
    BilinkedNode* node = list->head;
    List* created = list_create(list->element_size);
    while (node) {
        if (test(node)) list_add(created, node->value);
        node = node->next;
    }
    return created;
}

int list_peek(List* list, void* buffer) {
    return list_first(list, buffer);
}

int list_pop(List* list, void* buffer) {
    if (list->head != NULL) {
        BilinkedNode* head = list->head;
        if (buffer) memcpy(buffer, head->value, list->element_size);
        head->next->prev = NULL;
        list->head = head->next;
        list->len--;
        bilinked_node_destroy(head);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

void list_relink(List* list, BilinkedNode* node) {
    // Change linking
    if (node->prev) {
        // Previous element exists
        node->prev->next = node->next;
    } else {
        // Node is head
        list->head = node->next;
    }
    if (node->next) {
        // Next element exists
        node->next->prev = node->prev;
    } else {
        // Node is tail
        list->tail = node->prev;
    }
}

int list_remove(List* list, size_t index, void* buffer) {
    if (0 <= index && index < list->len) {
        // Loop througt the list starting at the head to find the node at
        // the given index.
        BilinkedNode* node = list->head;
        for (size_t i = 0; i < index; i++) {
            node = node->next;
        }

        if (buffer) memcpy(buffer, node->value, list->element_size);
        list_relink(list, node);

        list->len--;
        bilinked_node_destroy(node);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int list_remove_obj(List* list, void* obj, size_t* buffer) {
    size_t i = 0;
    for (BilinkedNode* node = list->head; node; node = node->next) {
        if (!memcmp(node->value, obj, list->element_size)) {
            memcpy(buffer, &i, sizeof(size_t));
            list_relink(list, node);

            // Decrease len of the list.
            list->len--;
            // Free allocated memory.
            bilinked_node_destroy(node);
            return EXIT_SUCCESS;
        }
        i++;
    }
    return EXIT_FAILURE;
}

void list_remove_if(List* list, Test test) {
    for (BilinkedNode* node = list->head; node; node = node->next) {
        if (test(node->value)) {
            list_relink(list, node);

            // Decrease len of the list.
            list->len--;
            // Free allocated memory.
            bilinked_node_destroy(node);
        }
    }
}

size_t list_len(List* list) {
    return list->len;
}

void list_clear(List* list) {
    if (list->head) {
        bilinked_node_destroy_recursive(list->head);
    }
    list->len = 0;
}

BilinkedNode** list_iter(List* list) {
    return &(list->head);
}

bool list_iter_has_next(BilinkedNode** iter) {
    return *iter != NULL;
}

void* list_iter_next(BilinkedNode** iter) {
    void* value = (*iter)->value;
    *iter = (*iter)->next;
    return value;
}

void* list_iter_peek(BilinkedNode** iter) {
    return (*iter)->value;
}
