#ifndef QUEUE_H
#define QUEUE_H

#include <assert.h>
#include <stdlib.h>
#include "elem.h"

typedef struct queue
{
    elem **arr;
    unsigned int max_size;
    unsigned int size;
    unsigned int front;
    unsigned int back;
} queue;

queue *create_queue(size_t n);
void clear_queue(queue *q);
void destroy_queue(queue *q);

int queue_empty(queue *q);
elem *queue_front(queue *q);
elem *queue_back(queue *q);
void queue_push(queue *q, elem *e);
void queue_pop(queue *q);

#endif