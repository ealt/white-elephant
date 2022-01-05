#include <string.h>
#include "simulate.h"

static void simulate_game(size_t n, unsigned int *perm, unsigned int *result)
{
    memcpy(result, perm, n * sizeof(unsigned int));
}

static unsigned long long *simulate_all_games(size_t n)
{
    unsigned long long *counts = (unsigned long long *)calloc(n * n, sizeof(unsigned long long));
    unsigned int *perm = init_perm(n);
    perm_state *st = create_perm_state(n);
    unsigned int *result = (unsigned int *)malloc(n * sizeof(unsigned int));
    while (!st->complete)
    {
        simulate_game(n, perm, result);
        update(n, counts, result);
        next(st, perm);
    }
    free(result);
    destroy_perm_state(st);
    free(perm);
    return counts;
}

PyObject *_simulate(PyObject *self, PyObject *args)
{
    size_t n;
    if (!PyArg_ParseTuple(args, "k", &n))
    {
        PyErr_BadArgument();
        return NULL;
    }
    int nd = 2;
    npy_intp dims[] = {n, n};
    unsigned long long *data = simulate_all_games(n);
    return PyArray_SimpleNewFromData(nd, dims, NPY_UINT64, data);
}