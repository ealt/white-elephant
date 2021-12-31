#include <Python.h>
#include "simulate.h"

static const char module_docstring[] = "Run white elephant simulations";

static PyMethodDef ModuleMethods[] = {
    {"simulate", (PyCFunction)_simulate, METH_NOARGS, "Runs simulations"},
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
    return m;
}