#include "consts.h"
#include "stack.h"

#ifndef TESTLIB_H
#define TESTLIB_H

	#define $( var , type )	printf("%s = %"type"\n", #var, (var));


	#define UNITTEST( what , ref )							\
		{													\
			if((what) != (ref)) {							\
				printf("UNIT TEST FAILED: %s = %d, expected: %d\n", #what, (what), (ref));	\
			}												\
		}

	#ifdef DEBUG
	#define myassert( check )								\
		{													\
			if (!(check))									\
				printf("%s, %d: Assertion %s failed\n",		\
				__FILE__, __LINE__, #check);				\
		}													
	#else
		#define myassert(check)  ;
	#endif


#endif

int runUnitTests();

data_t TestStackPushPop(data_t num);
int TestStackSizeDecrease();
int TestStackSizeIncrease(int elems);