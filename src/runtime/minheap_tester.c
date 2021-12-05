#include "minheap.h"
#include <stdio.h>

int main()
{
    struct min_heap heap = init_min_heap();
    int node_val[10] = { 8, 3, 7, 2, 1, 4, 9, 5, 6, 0 };

    for (int i = 0; i < 10; i++) {
        heap_push(&heap, node_val[i]);
        printf("Pushed %d\n", node_val[i]);
    }

    for (int i = 0; i < 10; i++) {
        printf("Popped %zu\n", heap_pop(&heap));
    }
    delete_heap(&heap);
}