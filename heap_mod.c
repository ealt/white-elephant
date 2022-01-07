#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include <stdlib.h>
#include <Python.h>
#include <numpy/arrayobject.h>
#include <numpy/ndarraytypes.h>
#include "elem.h"
#include "heap.h"

static PyObject *_get_mins(PyObject *self, PyObject *args)
{
    PyArrayObject *input;
    if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &input))
    {
        PyErr_BadArgument();
        return NULL;
    }
    npy_intp n = PyArray_DIM(input, 0);
    unsigned int *input_data = PyArray_DATA(input);
    int nd = 1;
    npy_intp dims[] = {n};
    unsigned int *data = (unsigned int *)malloc(n * sizeof(unsigned int));
    elem *arr = create_elem_arr(n);
    heap *h = create_heap(n);
    for (unsigned int i = 0; i < n; i++)
    {
        heap_push(h, &arr[input_data[i]]);
        data[i] = heap_top(h)->key;
    }
    destroy_heap(h);
    destroy_elem_arr(arr);
    return PyArray_SimpleNewFromData(nd, dims, NPY_UINT32, data);
}

static PyObject *_heap_sort(PyObject *self, PyObject *args)
{
    PyArrayObject *input;
    if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &input))
    {
        PyErr_BadArgument();
        return NULL;
    }
    npy_intp n = PyArray_DIM(input, 0);
    unsigned int *input_data = PyArray_DATA(input);
    int nd = 1;
    npy_intp dims[] = {n};
    unsigned int *data = (unsigned int *)malloc(n * sizeof(unsigned int));
    elem *arr = create_elem_arr(n);
    heap *h = create_heap(n);
    for (unsigned int i = 0; i < n; i++)
    {
        heap_push(h, &arr[input_data[i]]);
    }
    for (unsigned int i = 0; i < n; i++)
    {
        data[i] = heap_top(h)->key;
        heap_pop(h);
    }
    destroy_heap(h);
    destroy_elem_arr(arr);
    return PyArray_SimpleNewFromData(nd, dims, NPY_UINT32, data);
}

static const char module_docstring[] = "Implements a heap";

static PyMethodDef ModuleMethods[] = {
    {"get_mins", (PyCFunction)_get_mins, METH_VARARGS, "Get min values of heap"},
    {"heap_sort", (PyCFunction)_heap_sort, METH_VARARGS, "Sorts an array"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef _module = {
    PyModuleDef_HEAD_INIT,
    "heap",
    module_docstring,
    -1,
    ModuleMethods,
    NULL,
    NULL,
    NULL,
    NULL};

PyObject *PyInit_heap(void)
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