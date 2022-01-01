#include "simulate.h"

static unsigned long long *get_counts(size_t n)
{
    size_t nd = 2;
    size_t dims[] = {n, n};
    CountArray *arr = create(nd, dims);
    unsigned long long *data = (unsigned long long *)malloc(arr->size * sizeof(unsigned long long));
    memcpy(data, arr->data, arr->size * sizeof(unsigned long long));
    destroy(arr);
    return data;
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