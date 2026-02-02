#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>
#include <stdbool.h>

typedef struct node {
    int32_t data;
    struct node *next;
    struct node *prev;

    void (*destroy)(struct node *node);
} node_t;

node_t *node_init(int32_t data);

typedef struct linked_list {
    node_t *head;
    node_t *tail;
    uint64_t size;

    node_t *(*find)(struct linked_list *self, int32_t data);
    bool (*contains)(struct linked_list *self, int32_t data);
    bool (*is_empty)(struct linked_list *self);
    bool (*is_cyclic)(struct linked_list *self);

    void (*append)(struct linked_list *self, int32_t data);
    void (*prepend)(struct linked_list *self, int32_t data);
    void (*remove)(struct linked_list *self, node_t *node);
    void (*traverse)(struct linked_list *self, void (*func)(int32_t data));
    void (*destroy)(struct linked_list *self);
} linked_list_t;

linked_list_t *linked_list_init(void);

#endif // LINKED_LIST_H
