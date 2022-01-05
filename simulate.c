#include "simulate.h"

static void simulate_game(size_t n, unsigned int *perm, unsigned int *result)
{
    unsigned int turn = 0;
    unsigned int active = 0;
    while (turn < n)
    {
        result[active] = perm[turn];
        turn++;
        active = turn;
    }
}

static unsigned long long *simulate_all_games(size_t n)
{
    unsigned long long *counts = (unsigned long long *)calloc(n * n, sizeof(unsigned long long));
    unsigned int *perm = init_perm(n);
    perm_state *st = create_perm_state(n);
    unsigned int *result = (unsigned int *)malloc(n * sizeof(unsigned int));
    while (!st->complete)
    {
        simulate_game(n, perm, result);
        update(n, counts, result);
        next(st, perm);
    }
    free(result);
    destroy_perm_state(st);
    free(perm);
    return counts;
}

static unsigned long long *simulate_random_games(size_t n, unsigned long k)
{
    unsigned long long *counts = (unsigned long long *)calloc(n * n, sizeof(unsigned long long));
    unsigned int *perm = init_perm(n);
    unsigned int *result = (unsigned int *)malloc(n * sizeof(unsigned int));
    for (unsigned long i = 0; i < k; i++)
    {
        rand_next(n, perm);
        simulate_game(n, perm, result);
        update(n, counts, result);
    }
    free(result);
    free(perm);
    return counts;
}

PyObject *_simulate(PyObject *self, PyObject *args, PyObject *kw)
{
    static char *keywords[] = {"n", "k", NULL};
    size_t n;
    unsigned long k = 0;
    if (!PyArg_ParseTupleAndKeywords(args, kw, "k|k", keywords, &n, &k))
    {
        PyErr_BadArgument();
        return NULL;
    }
    int nd = 2;
    npy_intp dims[] = {n, n};
    unsigned long long *data;
    if (k)
    {
        data = simulate_random_games(n, k);
    }
    else
    {
        data = simulate_all_games(n);
    }
    return PyArray_SimpleNewFromData(nd, dims, NPY_UINT64, data);
}