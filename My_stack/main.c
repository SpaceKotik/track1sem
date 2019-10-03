//--------------------------------------------------------------------------------------------
//! @author SpaceKotik
//! @file	main.c
//! Main file of the project.
//--------------------------------------------------------------------------------------------

#include "consts.h"
#include "testlib.h"
#include "stack.h"

//--------------------------------------------------------------------------------------------
//! @fn main
//! Main function of project.
//--------------------------------------------------------------------------------------------

int main() {
	runUnitTests();

	stack *s = NULL;
	if ((s = StackCtor()) == NULL)
		return ALLOC_FAIL;
	//printf("size = %lu capacity = %lu last element = %d \n", s->size, s->capacity, s->data[s->size-1]);

	StackDtor(s);

	return 0;
}