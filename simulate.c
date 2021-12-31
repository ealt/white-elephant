#include "simulate.h"

PyObject *_simulate(PyObject *self)
{
    int nd = 2;
    npy_intp dims[] = {3, 4};
    int *data = (int *)calloc(12, sizeof(int));
    return PyArray_SimpleNewFromData(nd, dims, NPY_INT32, data);
}