#ifndef SIMULATE_H
#define SIMULATE_H

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#define NO_IMPORT_ARRAY
#define PY_ARRAY_UNIQUE_SYMBOL white_elephant_ARRAY_API

#include <stdlib.h>
#include <Python.h>
#include <numpy/arrayobject.h>
#include "count_array.h"
#include "heap.h"
#include "perm_iter.h"

PyObject *_simulate(PyObject *self, PyObject *args, PyObject *kw);

#endif