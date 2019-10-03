//--------------------------------------------------------------------------------------------
//! @author SpaceKotik
//! @file	testlib.c
//! File containing all testing functions.
//--------------------------------------------------------------------------------------------

#include "consts.h"
#include "testlib.h"
#include "stack.h"


//--------------------------------------------------------------------------------------------
//! @fn unUnitTests()
//! Runs unit tests.
//!
//! @return		Always returns 0 (for now at least).
//--------------------------------------------------------------------------------------------

int runUnitTests() {
	UNITTEST(TestStackPushPop(567), 567);
	UNITTEST(TestStackSizeDecrease(), 2);
	UNITTEST(TestStackSizeIncrease(350), 512);
	return 0;
}

//--------------------------------------------------------------------------------------------
//! @fn TestStackPushPop(data_t num)
//! Pushes some elements to stack and returns bottom one.
//!
//! @param[in]  num		element that should be returned.
//!
//! @return		Returns (num) element.
//--------------------------------------------------------------------------------------------

data_t TestStackPushPop(data_t num) {
	stack *s;
	s = StackCtor();
	StackPush(s, num);
	StackPush(s, 1);
	StackPush(s, 2);
	StackPush(s, 3);
	StackPop(s);
	StackPop(s);
	StackPop(s);
	data_t temp = StackPop(s);
	StackDtor(s);
	return temp;
}


//--------------------------------------------------------------------------------------------
//! @fn TestStackSizeDecrease()
//! Pushes some elements and removes them to check if realloc is working.
//!
//! @return		Returns capacity of the stack.
//--------------------------------------------------------------------------------------------

int TestStackSizeDecrease() {
	stack *s;
	s = StackCtor();
	for (int i = 1; i <= 10000; i++) {
		StackPush(s, i);
	}
	for (int i = 0; i < 10000; i++) {
		StackPop(s);
	}
	int temp = s->capacity;
	StackDtor(s);
	return temp;
}

//--------------------------------------------------------------------------------------------
//! @fn TestStackSizeIncrease(int elems)
//! Pushes (num) elements to check if realloc is working.
//!
//! @param[in]  elems		Number of elements to push.
//!
//! @return		Returns capacity of the stack.
//--------------------------------------------------------------------------------------------

int TestStackSizeIncrease(int elems) {
	stack *s;
	if((s = StackCtor()) == NULL)
		return ALLOC_FAIL;
	for (int i = 1; i <= elems; i++) {
		StackPush(s, i);
	}
	int temp = s->capacity;
	StackDtor(s);
	return temp;
}