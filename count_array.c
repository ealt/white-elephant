#include "count_array.h"

static void set_offsets(CountArray *arr)
{
    arr->offsets[arr->nd - 1] = 1;
    for (unsigned int i = arr->nd - 1; i > 0; i--)
    {
        arr->offsets[i - 1] = arr->offsets[i] * arr->dims[i];
    }
}

static unsigned int idxs_to_idx(CountArray *arr, unsigned int idxs[])
{
    unsigned int idx = 0;
    for (unsigned int i = 0; i < arr->nd; i++)
    {
        idx += idxs[i] * arr->offsets[i];
    }
    return idx;
}

CountArray *create(size_t nd, size_t dims[])
{
    CountArray *arr = (CountArray *)malloc(sizeof(CountArray));
    arr->nd = nd;
    arr->dims = (size_t *)malloc(nd * sizeof(size_t));
    memcpy(arr->dims, dims, nd * sizeof(size_t));
    arr->offsets = (size_t *)malloc(nd * sizeof(size_t));
    set_offsets(arr);
    arr->size = arr->dims[0] * arr->offsets[0];
    arr->data = (unsigned long long *)calloc(arr->size, sizeof(unsigned long long));
    return arr;
}

void clear(CountArray *arr)
{
    memset(arr->data, 0, arr->size * sizeof(unsigned long long));
}

void destroy(CountArray *arr)
{
    free(arr->dims);
    free(arr->offsets);
    free(arr->data);
    free(arr);
    arr = NULL;
}

unsigned long long get(CountArray *arr, unsigned int idxs[])
{
    return arr->data[idxs_to_idx(arr, idxs)];
}

void set(CountArray *arr, unsigned int idxs[], unsigned long long val)
{
    arr->data[idxs_to_idx(arr, idxs)] = val;
}