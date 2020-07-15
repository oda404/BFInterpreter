// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

//basic ass stack implementation
#ifndef STACK_H
#define STACK_H

#include<stdlib.h>

typedef struct
{
    long unsigned int size;
    int *items;
} stack;

void push(stack *s, int item);
int top(stack *s);
void pop(stack *s);
void freeStack(stack *s);

#endif //STACK_H
