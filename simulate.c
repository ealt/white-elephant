#include "simulate.h"

static unsigned long long *get_counts(void)
{
    size_t nd = 2;
    size_t dims[] = {3, 4};
    CountArray *arr = create(nd, dims);
    unsigned long long *data = (unsigned long long *)malloc(arr->size * sizeof(unsigned long long));
    memcpy(data, arr->data, arr->size * sizeof(unsigned long long));
    destroy(arr);
    return data;
}

PyObject *_simulate(PyObject *self)
{
    int nd = 2;
    npy_intp dims[] = {3, 4};
    unsigned long long *data = get_counts();
    return PyArray_SimpleNewFromData(nd, dims, NPY_UINT64, data);
}