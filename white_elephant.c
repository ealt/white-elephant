#include <Python.h>

PyObject *_hello_world(PyObject *self)
{
    printf("Hello, World!\n");
    Py_RETURN_NONE;
}

static const char module_docstring[] = "Run white elephant simulations";

static PyMethodDef ModuleMethods[] = {
    {"hello_world", (PyCFunction)_hello_world, METH_NOARGS, "Prints Hello, world!"},
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