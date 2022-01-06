#include "perm_iter.h"

static void swap(unsigned int *arr, unsigned int i, int j)
{
    unsigned int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

unsigned int *create_perm(size_t n)
{
    unsigned int *arr = (unsigned int *)malloc(n * sizeof(unsigned int));
    for (unsigned int i = 0; i < n; i++)
    {
        arr[i] = i;
    }
    return arr;
}

void destroy_perm(unsigned int *perm)
{
    free(perm);
    perm = NULL;
}

perm_state *create_perm_state(size_t n)
{
    perm_state *st = (perm_state *)malloc(sizeof(perm_state));
    st->n = n;
    st->c = (unsigned int *)calloc(n, sizeof(unsigned int));
    st->i = 0;
    st->complete = 0;
    return st;
}

void destroy_perm_state(perm_state *st)
{
    free(st->c);
    free(st);
    st = NULL;
}

void next(perm_state *st, unsigned int *arr)
// https://en.wikipedia.org/wiki/Heap%27s_algorithm
{
    while (st->i < st->n)
    {
        if (st->c[st->i] < st->i)
        {
            if (st->i % 2 == 0)
            {
                swap(arr, 0, st->i);
            }
            else
            {
                swap(arr, st->c[st->i], st->i);
            }
            st->c[st->i]++;
            st->i = 0;
            return;
        }
        else
        {
            st->c[st->i] = 0;
            st->i++;
        }
    }
    st->complete = 1;
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