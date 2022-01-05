#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#define PY_ARRAY_UNIQUE_SYMBOL white_elephant_ARRAY_API

#include <Python.h>
#include <numpy/arrayobject.h>
#include <numpy/ndarraytypes.h>
#include "simulate.h"

static const char module_docstring[] = "Run white elephant simulations";

static PyMethodDef ModuleMethods[] = {
    {"simulate", (PyCFunction)_simulate, METH_VARARGS | METH_KEYWORDS, "Runs simulations"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef _module = {
    PyModuleDef_HEAD_INIT,
    "white_elephant",
    module_docstring,
    -1,
    ModuleMethods,
    NULL,
    NULL,
    NULL,
    NULL};

PyObject *PyInit_white_elephant(void)
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