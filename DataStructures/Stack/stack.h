#ifndef _STACK_H_
#define _STACK_H_

#include "stdlib.h"

typedef struct
{
    short* data;
    size_t size;
    size_t capacity;
}
Stack;

Stack* stack_create(size_t init_capacity);

void stack_push(Stack* stack, short elem);
short stack_pop(Stack* stack);
short stack_peek(Stack* stack);

void stack_delete(Stack* stack);

#endif
