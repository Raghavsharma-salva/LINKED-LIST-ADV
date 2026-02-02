#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "collection/linked_list.h"

void print_node(int32_t data) {
    printf("Node data: %d\n", data);
}

int main(void) {
    linked_list_t *list = linked_list_init();
    if (list == NULL) {
        perror("Failed to initialize linked list");
        return EXIT_FAILURE;
    }

    list->append(list, 10);
    list->append(list, 20);
    list->prepend(list, 5);
    printf("List size: %" PRIu64 "\n", list->size);

    list->traverse(list, print_node);

    list->destroy(list);

    return EXIT_SUCCESS;
}
