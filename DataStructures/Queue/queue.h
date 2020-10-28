#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "stdlib.h"

typedef struct QueueNode
{
    short data;
    struct QueueNode* ptr_next;
}
QueueNode;

typedef struct
{
    QueueNode *front, *rear;
    size_t size;
}
Queue;

Queue* queue_create();

void queue_push(Queue* queue, short elem);
short queue_pop(Queue* queue);

short queue_front(Queue* queue);
short queue_rear(Queue* queue);

void queue_print(Queue* queue);

void queue_delete(Queue* queue);

#endif
