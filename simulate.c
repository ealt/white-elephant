#include "simulate.h"

unsigned int *create_result(size_t n)
{
    unsigned int *result = (unsigned int *)malloc(n * sizeof(unsigned int));
    return result;
}

void destroy_result(unsigned int *result)
{
    free(result);
    result = NULL;
}

typedef struct sim_data
{
    size_t n;
    unsigned int *perm;
    unsigned int *result;
    elem *arr;
    heap *h;
    queue *q;
    unsigned int turn;
    unsigned int active;
    unsigned int next_active;
} sim_data;

sim_data create_sim_data(size_t n)
{
    struct sim_data sd =
        {
            n,
            create_perm(n),
            create_result(n),
            create_elem_arr(n),
            create_heap(n),
            create_queue(n),
            0,
            0,
            0,
        };
    return sd;
}

void reset_sim_data(sim_data *sd)
{
    clear_heap(sd->h);
    clear_queue(sd->q);
    sd->turn = 0;
    sd->active = 0;
}

void destory_sim_data(sim_data *sd)
{
    destroy_perm(sd->perm);
    destroy_result(sd->result);
    destroy_elem_arr(sd->arr);
    destroy_heap(sd->h);
    destroy_queue(sd->q);
}

static int steal(void)
// TODO
{
    return 0;
}

static void simulate_game(sim_data *sd)
{
    while (sd->turn < sd->n)
    {
        if (steal())
        {
            queue_push(sd->q, heap_top(sd->h));
            heap_pop(sd->h);
            sd->result[sd->active] = queue_back(sd->q)->key;
            sd->next_active = queue_back(sd->q)->owner;
            queue_back(sd->q)->owner = sd->active;
            sd->active = sd->next_active;
        }
        else
        {
            sd->result[sd->active] = sd->perm[sd->turn];
            sd->arr[sd->perm[sd->turn]].owner = sd->active;
            queue_push(sd->q, &sd->arr[sd->perm[sd->turn]]);
            while (!queue_empty(sd->q))
            {
                heap_push(sd->h, queue_front(sd->q));
                queue_pop(sd->q);
            }
            sd->turn++;
            sd->active = sd->turn;
        }
    }
}

static unsigned long long *simulate_all_games(size_t n)
{
    unsigned long long *counts = (unsigned long long *)calloc(n * n, sizeof(unsigned long long));
    perm_state *st = create_perm_state(n);
    sim_data sd = create_sim_data(n);
    while (!perm_complete(st))
    {
        simulate_game(&sd);
        update(n, counts, sd.result);
        reset_sim_data(&sd);
        next(st, sd.perm);
    }
    destory_sim_data(&sd);
    destroy_perm_state(st);
    return counts;
}

static unsigned long long *simulate_random_games(size_t n, unsigned long k)
{
    unsigned long long *counts = (unsigned long long *)calloc(n * n, sizeof(unsigned long long));
    sim_data sd = create_sim_data(n);
    for (unsigned long i = 0; i < k; i++)
    {
        rand_next(n, sd.perm);
        simulate_game(&sd);
        update(n, counts, sd.result);
        reset_sim_data(&sd);
    }
    destory_sim_data(&sd);
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