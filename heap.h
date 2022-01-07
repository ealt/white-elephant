#ifndef HEAP_H
#define HEAP_H

#include <assert.h>
#include <stdlib.h>

typedef struct elem
{
    unsigned int key;
    unsigned int owner;
} elem;

elem *create_elem_list(size_t n);
void destroy_elem_list(elem *el);

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