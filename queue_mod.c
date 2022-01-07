#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include <math.h>
#include <stdlib.h>
#include <Python.h>
#include <numpy/arrayobject.h>
#include <numpy/ndarraytypes.h>
#include "elem.h"
#include "queue.h"

static PyObject *_push_pop(PyObject *self, PyObject *args)
{
    size_t n;
    PyArrayObject *input;
    unsigned long k = 0;
    if (!PyArg_ParseTuple(args, "kO!k", &n, &PyArray_Type, &input, &k))
    {
        PyErr_BadArgument();
        return NULL;
    }
    npy_intp input_size = PyArray_DIM(input, 0);
    unsigned int *input_data = PyArray_DATA(input);
    unsigned long m = (unsigned int)floor(input_size / k);
    int nd = 1;
    npy_intp dims[] = {k * m};
    unsigned int *data = (unsigned int *)malloc(k * m * sizeof(unsigned int));
    elem *arr = create_elem_arr(n);
    queue *q = create_queue(n);
    for (unsigned int i = 0; i < m; i++)
    {
        for (unsigned int j = 0; j < k; j++)
        {
            push(q, &arr[input_data[(i * k) + j]]);
        }
        for (unsigned int j = 0; j < k; j++)
        {
            data[(i * k) + j] = top(q)->key;
            pop(q);
        }
    }
    destroy_queue(q);
    destroy_elem_arr(arr);
    return PyArray_SimpleNewFromData(nd, dims, NPY_UINT32, data);
}

static const char module_docstring[] = "Implements a queue";

static PyMethodDef ModuleMethods[] = {
    {"push_pop", (PyCFunction)_push_pop, METH_VARARGS, "Push then pop values of heap"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef _module = {
    PyModuleDef_HEAD_INIT,
    "my_queue",
    module_docstring,
    -1,
    ModuleMethods,
    NULL,
    NULL,
    NULL,
    NULL};

PyObject *PyInit_my_queue(void)
{
    PyObject *m;
    m = PyModule_Create(&_module);
    if (!m)
    {
        return NULL;
    }
    import_array();
    return m;
}