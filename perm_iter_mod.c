#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include <stdlib.h>
#include <string.h>
#include <Python.h>
#include <numpy/arrayobject.h>
#include <numpy/ndarraytypes.h>
#include "perm_iter.h"

static unsigned long factorial(size_t n)
{
    unsigned long x = 1;
    for (unsigned long i = 1; i <= n; i++)
    {
        x *= i;
    }
    return x;
}

static unsigned int *get_data(size_t n)
{
    unsigned int *arr = create_perm(n);
    perm_state *st = create_perm_state(n);
    unsigned long fn = factorial(n);
    unsigned int *data = (unsigned int *)malloc(fn * n * sizeof(unsigned int));
    for (unsigned long i = 0; i < fn; i++)
    {
        if (perm_complete(st))
        {
            PyErr_SetString(PyExc_RuntimeError, "Premature permutation complete");
            free(data);
            data = NULL;
            break;
        }
        memcpy(data + (i * n), arr, n * sizeof(unsigned int));
        next(st, arr);
    }
    if (!perm_complete(st))
    {
        PyErr_SetString(PyExc_RuntimeError, "Permutation incomplete");
        free(data);
        data = NULL;
    }
    destroy_perm_state(st);
    destroy_perm(arr);
    return data;
}

static PyObject *_get_perms(PyObject *self, PyObject *args)
{
    size_t n;
    if (!PyArg_ParseTuple(args, "k", &n))
    {
        PyErr_BadArgument();
        return NULL;
    }
    int nd = 2;
    npy_intp dims[] = {factorial(n), n};
    unsigned int *data = get_data(n);
    return PyArray_SimpleNewFromData(nd, dims, NPY_UINT32, data);
}

static unsigned int *get_rand_data(size_t n, unsigned int k)
{
    srand(42);
    unsigned int *data = (unsigned int *)malloc(n * k * sizeof(unsigned int));
    unsigned int *arr = create_perm(n);
    for (unsigned int i = 0; i < k; i++)
    {
        memcpy(data + (i * n), arr, n * sizeof(unsigned int));
        rand_next(n, arr);
    }
    destroy_perm(arr);
    return data;
}

static PyObject *_get_rand_perms(PyObject *self, PyObject *args)
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
    unsigned int *data = get_rand_data(n, k);
    return PyArray_SimpleNewFromData(nd, dims, NPY_UINT32, data);
}

static const char module_docstring[] = "Get permutations";

static PyMethodDef ModuleMethods[] = {
    {"get_perms", (PyCFunction)_get_perms, METH_VARARGS, "Get permutations"},
    {"get_rand_perms", (PyCFunction)_get_rand_perms, METH_VARARGS, "Get random permutations"},
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