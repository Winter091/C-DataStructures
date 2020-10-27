#include "stack.h"

#include "../mem_debugger.h"

Stack* stack_create(size_t init_capacity)
{
    Stack* stack = malloc(sizeof(Stack));

    stack->size = 0;
    stack->capacity = init_capacity;
    stack->data = malloc(stack->capacity * sizeof(short));

    return stack;
}

void stack_push(Stack* stack, short elem)
{
    if (++stack->size > stack->capacity)
    {
        if (!stack->capacity) stack->capacity = 1;
        stack->capacity *= 2;
        stack->data = realloc(stack->data, stack->capacity * sizeof(short));
    }

    stack->data[stack->size - 1] = elem;
}

short stack_pop(Stack* stack)
{
    if (stack->size > 0)
    {
        stack->size--;
        return stack->data[stack->size];
    }
}

short stack_peek(Stack* stack)
{
    if (stack->size > 0)
        return stack->data[stack->size - 1];
}

void stack_delete(Stack* stack)
{
    free(stack->data);
    free(stack);
}
