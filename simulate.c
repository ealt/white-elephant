#include "simulate.h"

static unsigned long long *get_counts(size_t n)
{
    unsigned long long *counts = (unsigned long long *)calloc(n * n, sizeof(unsigned long long));
    unsigned int *result = init_perm(n);
    perm_state *st = create_perm_state(n);
    update(n, counts, result);
    next(st, result);
    update(n, counts, result);
    destroy_perm_state(st);
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
    unsigned long long *data = get_counts(n);
    return PyArray_SimpleNewFromData(nd, dims, NPY_UINT64, data);
}