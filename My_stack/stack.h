#include "consts.h"
#ifndef STACK_H
#define STACK_H


typedef struct Stack {
	data_t *data;
	size_t size;
	size_t capacity;
} stack;

int StackOk(stack *s);

stack* StackCtor();

void StackDtor(stack *s);

int StackPush(stack *s, data_t var);

data_t StackPop(stack *s);

int StackClear(stack *s);

#endif