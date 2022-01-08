#include "queue.h"

typedef struct queue
{
    elem **arr;
    unsigned int max_size;
    unsigned int size;
    unsigned int front;
    unsigned int back;
} queue;

queue *create_queue(size_t n)
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->arr = (elem **)malloc(n * sizeof(elem *));
    q->max_size = n;
    q->size = 0;
    q->front = 0;
    q->back = n - 1;
    return q;
}
void clear_queue(queue *q)
{
    q->size = 0;
    q->front = 0;
    q->back = q->max_size - 1;
}

void destroy_queue(queue *q)
{
    free(q->arr);
    free(q);
    q = NULL;
}

int queue_empty(queue *q)
{
    return q->size == 0;
}

elem *queue_front(queue *q)
{
    assert(!queue_empty(q));
    return q->arr[q->front];
}

elem *queue_back(queue *q)
{
    assert(!queue_empty(q));
    return q->arr[q->back];
}

void queue_push(queue *q, elem *e)
{
    assert(q->size < q->max_size);
    q->back = (q->back + 1) % q->max_size;
    q->arr[q->back] = e;
    q->size++;
}

void queue_pop(queue *q)
{
    assert(!queue_empty(q));
    q->front = (q->front + 1) % q->max_size;
    q->size--;
}