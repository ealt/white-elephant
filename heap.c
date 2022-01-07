#include "heap.h"

elem *create_elem_list(size_t n)
{
    elem *el = (elem *)malloc(n * sizeof(elem));
    for (unsigned int i = 0; i < n; i++)
    {
        el[i].key = i;
    }
    return el;
}

void destroy_elem_list(elem *el)
{
    free(el);
    el = NULL;
}

heap *create_heap(size_t n)
{
    heap *h = (heap *)malloc(sizeof(heap));
    h->tree = (elem **)malloc(n * sizeof(elem *));
    h->max_size = n;
    h->size = 0;
    return h;
}

void clear_heap(heap *h)
{
    h->size = 0;
}

void destroy_heap(heap *h)
{
    free(h->tree);
    free(h);
    h = NULL;
}

elem *top(heap *h)
{
    assert(h->size);
    return h->tree[0];
}

static void swap(heap *h, unsigned int i, unsigned int j)
{
    elem *temp = h->tree[i];
    h->tree[i] = h->tree[j];
    h->tree[j] = temp;
}

static void heapify_up(heap *h, unsigned int child)
{
    unsigned int parent = child / 2;
    if (h->tree[child]->key < h->tree[parent]->key)
    {
        swap(h, parent, child);
        heapify_up(h, parent);
    }
}

void push(heap *h, elem *e)
{
    assert(h->size < h->max_size);
    h->tree[h->size] = e;
    h->size++;
    heapify_up(h, h->size - 1);
}

static void heapify_down(heap *h, unsigned int parent)
{
    unsigned int min_idx = parent;
    unsigned int child = parent * 2;
    if ((child < h->size) && (h->tree[child]->key < h->tree[min_idx]->key))
    {
        min_idx = child;
    }
    child++;
    if ((child < h->size) && (h->tree[child]->key < h->tree[min_idx]->key))
    {
        min_idx = child;
    }
    if (min_idx != parent)
    {
        swap(h, parent, min_idx);
        heapify_down(h, min_idx);
    }
}

void pop(heap *h)
{
    assert(h->size);
    h->size--;
    if (h->size)
    {
        h->tree[0] = h->tree[h->size];
        heapify_down(h, 0);
    }
}