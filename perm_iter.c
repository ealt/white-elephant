#include "perm_iter.h"

static void swap(unsigned int *arr, unsigned int i, int j)
{
    unsigned int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

unsigned int *init_perm(size_t n)
{
    unsigned int *arr = (unsigned int *)malloc(n * sizeof(unsigned int));
    for (unsigned int i = 0; i < n; i++)
    {
        arr[i] = i;
    }
    return arr;
}

void rand_next(size_t n, unsigned int *arr)
// https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
{
    int j;
    for (unsigned int i = n - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        swap(arr, i, j);
    }
}