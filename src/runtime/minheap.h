#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    size_t data;
} node;

typedef struct min_heap {
    size_t size;
    size_t capacity;
    node* elem;
} min_heap;

min_heap init_min_heap()
{
    min_heap heap;
    heap.size = 0;
    heap.capacity = 10;
    heap.elem = malloc(10 * sizeof(node));
    return heap;
}

void increase_heap_size(min_heap* heap)
{
    if (heap->size) {
        heap->elem = realloc(heap->elem, (heap->size + 10) * sizeof(node));
    }
}

void heap_push(min_heap* heap, size_t data)
{
    if (heap->size >= heap->capacity) {
        increase_heap_size(heap);
    }

    node nd;
    nd.data = data;

    int i = (heap->size)++;
    while (i && nd.data < heap->elem[PARENT(i)].data) {
        heap->elem[i] = heap->elem[PARENT(i)];
        i = PARENT(i);
    }
    heap->elem[i] = nd;
}

void swap(node* n1, node* n2)
{
    node t = *n1;
    *n1 = *n2;
    *n2 = t;
}

void heapify(min_heap* heap, int i)
{
    int smallest = (LCHILD(i) < heap->size && heap->elem[LCHILD(i)].data < heap->elem[i].data) ? LCHILD(i) : i;
    if (RCHILD(i) < heap->size && heap->elem[RCHILD(i)].data < heap->elem[smallest].data) {
        smallest = RCHILD(i);
    }
    if (smallest != i) {
        swap(&(heap->elem[i]), &(heap->elem[smallest]));
        heapify(heap, smallest);
    }
}

size_t heap_pop(min_heap* heap)
{
    size_t data = heap->elem[0].data;
    if (heap->size) {
        heap->elem[0] = heap->elem[--(heap->size)];
        heap->elem = realloc(heap->elem, heap->size * sizeof(node));
        heapify(heap, 0);
    }
    return data;
}

void delete_heap(min_heap* heap)
{
    while (heap->size > 0) {
        heap_pop(heap);
    }
    free(heap->elem);
}
