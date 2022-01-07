#ifndef ELEM_H
#define ELEM_H

#include <stdlib.h>

typedef struct elem
{
    unsigned int key;
    unsigned int owner;
} elem;

elem *create_elem_arr(size_t n);
void destroy_elem_arr(elem *el);

#endif