#ifndef QUEUE_H
#define QUEUE_H

#include <assert.h>
#include <stdlib.h>
#include "elem.h"

typedef struct queue
{
    elem **arr;
    unsigned int max_size;
    unsigned int first;
    unsigned int next;
} queue;

queue *create_queue(size_t n);
void clear_queue(queue *q);
void destroy_queue(queue *q);

elem *queue_top(queue *q);
void queue_push(queue *q, elem *e);
void queue_pop(queue *q);

#endif