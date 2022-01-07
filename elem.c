#include "elem.h"

elem *create_elem_arr(size_t n)
{
    elem *arr = (elem *)malloc(n * sizeof(elem));
    for (unsigned int i = 0; i < n; i++)
    {
        arr[i].key = i;
    }
    return arr;
}

void destroy_elem_arr(elem *arr)
{
    free(arr);
    arr = NULL;
}