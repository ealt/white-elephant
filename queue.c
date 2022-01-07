#include "queue.h"

queue *create_queue(size_t n)
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->arr = (elem **)malloc(n * sizeof(elem *));
    q->max_size = n;
    q->first = 0;
    q->next = 0;
    return q;
}
void clear_queue(queue *q)
{
    q->first = 0;
    q->next = 0;
}

void destroy_queue(queue *q)
{
    free(q->arr);
    free(q);
    q = NULL;
}

elem *queue_top(queue *q)
{
    assert(q->first != q->next);
    return q->arr[q->first];
}

void queue_push(queue *q, elem *e)
{
    unsigned int next_next = (q->next + 1) % q->max_size;
    assert(next_next != q->first);
    q->arr[q->next] = e;
    q->next = next_next;
}

void queue_pop(queue *q)
{
    assert(q->first != q->next);
    q->first = (q->first + 1) % q->max_size;
}