#ifndef COUNT_ARRAY
#define COUNT_ARRAY

#include <stdlib.h>
#include <string.h>

typedef struct
{
    size_t size;
    size_t nd;
    size_t *dims;
    size_t *offsets;
    unsigned long long *data;
} CountArray;

CountArray *create(size_t nd, size_t dims[]);
void clear(CountArray *arr);
void destroy(CountArray *arr);

unsigned long long get(CountArray *arr, unsigned int idxs[]);
void set(CountArray *arr, unsigned int idxs[], unsigned long long val);

#endif