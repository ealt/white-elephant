#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include <stdlib.h>
#include <string.h>
#include <Python.h>
#include <numpy/arrayobject.h>
#include <numpy/ndarraytypes.h>
#include "perm_iter.h"

static unsigned int *get_data(size_t n, unsigned int k)
{
    srand(42);
    unsigned int *data = (unsigned int *)malloc(n * k * sizeof(unsigned int));
    unsigned int *arr = init_perm(n);
    for (unsigned int i = 0; i < k; i++)
    {
        memcpy(data + (i * n), arr, n * sizeof(unsigned int));
        rand_next(n, arr);
    }
    return data;
}

static PyObject *_get_perms(PyObject *self, PyObject *args)
{
    size_t n;
    unsigned int k;
    if (!PyArg_ParseTuple(args, "kI", &n, &k))
    {
        PyErr_BadArgument();
        return NULL;
    }
    int nd = 2;
    npy_intp dims[] = {k, n};
    unsigned int *data = get_data(n, k);
    return PyArray_SimpleNewFromData(nd, dims, NPY_UINT32, data);
}

static const char module_docstring[] = "Get permutations";

static PyMethodDef ModuleMethods[] = {
    {"get_perms", (PyCFunction)_get_perms, METH_VARARGS, "Get permutations"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef _module = {
    PyModuleDef_HEAD_INIT,
    "perm_iter",
    module_docstring,
    -1,
    ModuleMethods,
    NULL,
    NULL,
    NULL,
    NULL};

PyObject *PyInit_perm_iter(void)
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