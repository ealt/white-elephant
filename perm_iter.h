#ifndef PERM_ITER_H
#define PERM_ITER_H

#include <stdlib.h>
#include <string.h>

typedef struct perm_state perm_state;

unsigned int *create_perm(size_t n);

void destroy_perm(unsigned int *perm);

perm_state *create_perm_state(size_t n);

void destroy_perm_state(perm_state *st);

int perm_complete(perm_state *st);

void next(perm_state *st, unsigned int *arr);

void rand_next(size_t n, unsigned int *arr);

#endif