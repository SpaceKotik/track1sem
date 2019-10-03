//--------------------------------------------------------------------------------------------
//! @author SpaceKotik
//! @file	stack.c
//! File containing all stack functions.
//--------------------------------------------------------------------------------------------

#include "consts.h"
#include "testlib.h"
#include "stack.h"

//--------------------------------------------------------------------------------------------
//! @fn StackOk(stack *s)
//! Checks basic stacks fields.
//!
//! @param[in]  *s 	Stack to check.
//!
//! @return		If stack size, capacity, data are invalid or if stack is ok returns STRUCT_FAIL, ALLOC_FAIL, DATA_FAIL or OK.
//--------------------------------------------------------------------------------------------

int StackOk(stack *s) {
	if (s->size < 0)
		return STRUCT_FAIL;

	if (s->capacity < 0)
		return ALLOC_FAIL;

	if (s->data == NULL)
		return DATA_FAIL;

	return OK;

}

//--------------------------------------------------------------------------------------------
//! @fn StackCtor()
//! Allocates memory for stack.
//!
//! @return		Returns stack* or NULL if allocation failed.
//--------------------------------------------------------------------------------------------

stack* StackCtor() {
	stack *s = malloc(sizeof(stack*));
	s->size = 0;
	s->capacity = 2;
	s->data = malloc(sizeof(data_t)*2);

	return s;
}

//--------------------------------------------------------------------------------------------
//! @fn StackDtor(stack *s)
//! Frees stack's memory.
//!
//! @return		Does not return anything
//--------------------------------------------------------------------------------------------

void StackDtor(stack *s) {
	myassert(s != NULL);
	free(s->data);
	s->capacity = -1;
	s->size = -1;
}

//--------------------------------------------------------------------------------------------
//! @fn StackPush(stack *s, data_t var)
//! Pushes an element to the stack.
//!
//! @param[in]  *s 		Current stack.
//! @param[in]  var 	Variable to push.
//!
//! @return		Always returns OK (for now at least).
//--------------------------------------------------------------------------------------------

int StackPush(stack *s, data_t var) {
	myassert(s != NULL);
	myassert(s->size >= 0);
	myassert(s->capacity > 0);
	myassert(StackOk(s) == OK);

	if (s->capacity < s->size + 1) {
		s->data = realloc(s->data, 2 * (s->capacity)*(sizeof(data_t)));
		s->capacity *= 2;
	}

	s->data[s->size++] = var;
	
	myassert(StackOk(s) == OK);
	return OK;
}

//--------------------------------------------------------------------------------------------
//! @fn StackPop(stack *s)
//! Pops top element of the stack.
//!
//! @param[in]  *s 		Current stack.
//!
//! @return		Returns top element of the stack.
//--------------------------------------------------------------------------------------------

data_t StackPop(stack *s) {
	myassert(s != NULL);
	myassert(s->size >= 0);
	myassert(s->capacity > 0);
	myassert(StackOk(s) == OK);

	if (s->capacity > (s->size)*2 && s->size != 0) {
		s->data = realloc(s->data, (s->capacity)*sizeof(data_t)/2);
		//assert(s->data != NULL);
		s->capacity /= 2;
	}

	myassert(StackOk(s) == OK);
	return s->data[--s->size];
}

//--------------------------------------------------------------------------------------------
//! @fnStackClear(stack *s)
//! Removes all elements ffrom the stack and decreases it's size.
//!
//! @param[in]  *s 		Current stack.
//!
//! @return		Returns OK or STRUCT_FAIL if stack cleared successfully or if stack is not ok.
//--------------------------------------------------------------------------------------------

int StackClear(stack *s) {
	if((StackOk(s) == OK)) {
		free(s->data);
		s->size = 0;
		s->capacity = 2;
		s->data = malloc(sizeof(data_t)*2);
		myassert(StackOk(s) == OK);
		return OK;

	}
	return STRUCT_FAIL;
}
