#ifndef HEAP_H
#define HEAP_H

#include <assert.h>
#include <stdlib.h>
#include "elem.h"

typedef struct heap
{
    elem **tree;
    unsigned int max_size;
    unsigned int size;
} heap;

heap *create_heap(size_t n);
void clear_heap(heap *h);
void destroy_heap(heap *h);

elem *heap_top(heap *h);
void heap_push(heap *h, elem *e);
void heap_pop(heap *h);

#endif