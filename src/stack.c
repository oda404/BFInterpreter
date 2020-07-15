// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"stack.h"

void push(stack *s, int item)
{
    int *newAlloc = (int*)realloc(s->items, ++s->size * sizeof(int));
    if(newAlloc)
    {
        s->items = newAlloc;
        s->items[s->size - 1] = item;
    }
    else
    {
        free(s->items);
        abort();
    }
}

int top(stack *s)
{
    return s->items[s->size - 1];
}

void pop(stack *s)
{
    s->items = (int*)realloc(s->items, --s->size * sizeof(int));
}

void freeStack(stack *s)
{
    free(s->items);
    s->size = 0;
}
