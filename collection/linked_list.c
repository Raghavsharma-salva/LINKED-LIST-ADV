#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

void node_destroy(node_t *node);

node_t *node_init(int32_t data) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) {
        perror("Failed to allocate memory for new node");
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->destroy = node_destroy;
    return new_node;
}

void node_destroy(node_t *node) {
    if (node != NULL) {
        free(node);
    } else {
        fprintf(stderr, "Attempted to destroy a NULL node\n");
    }
}

node_t *find(struct linked_list *self, int32_t data);
bool contains(struct linked_list *self, int32_t data);
bool is_empty(struct linked_list *self);
bool is_cyclic(struct linked_list *self);

void append(struct linked_list *self, int32_t data);
void prepend(struct linked_list *self, int32_t data);
void remove_node(struct linked_list *self, node_t *node);
void destroy(struct linked_list *self);

void traverse(struct linked_list *self, void (*func)(int32_t data));

linked_list_t *linked_list_init(void) {
    linked_list_t *list = (linked_list_t *)malloc(sizeof(linked_list_t));
    if (list == NULL) {
        perror("Failed to allocate memory for linked list");
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    list->find = find;
    list->contains = contains;
    list->is_empty = is_empty;
    list->is_cyclic = is_cyclic;

    list->append = append;
    list->prepend = prepend;
    list->remove = remove_node;
    list->traverse = traverse;
    list->destroy = destroy;


    return list;
}

node_t *find(struct linked_list *self, int32_t data) {
    node_t *current = self->head;
    while (current != NULL) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

bool contains(struct linked_list *self, int32_t data) {
    return find(self, data) != NULL;
}

bool is_empty(struct linked_list *self) {
    return self->size == 0;
}

bool is_cyclic(struct linked_list *self) {
    node_t *slow = self->head;
    node_t *fast = self->head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }
    return false;
}

void append(struct linked_list *self, int32_t data) {
    node_t *new_node = node_init(data);
    if (new_node == NULL) {
        return;
    }
    if (self->tail == NULL) {
        self->head = new_node;
        self->tail = new_node;
    } else {
        self->tail->next = new_node;
        new_node->prev = self->tail;
        self->tail = new_node;
    }
    self->size++;
}

void prepend(struct linked_list *self, int32_t data) {
    node_t *new_node = node_init(data);
    if (new_node == NULL) {
        return;
    }
    if (self->head == NULL) {
        self->head = new_node;
        self->tail = new_node;
    } else {
        new_node->next = self->head;
        self->head->prev = new_node;
        self->head = new_node;
    }
    self->size++;
}

void remove_node(struct linked_list *self, node_t *node) {
    if (node == NULL || self->head == NULL) {
        return;
    }

    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        self->head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        self->tail = node->prev;
    }

    node->destroy(node);
    self->size--;
}

void traverse(struct linked_list *self, void (*func)(int32_t data)) {
    node_t *current = self->head;
    while (current != NULL) {
        func(current->data);
        current = current->next;
    }
}

void destroy(struct linked_list *self) {
    node_t *current = self->head;
    while (current != NULL) {
        node_t *next = current->next;
        current->destroy(current);
        current = next;
    }
    free(self);
}
