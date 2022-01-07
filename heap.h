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

elem *top(heap *h);
void push(heap *h, elem *e);
void pop(heap *h);

#endif