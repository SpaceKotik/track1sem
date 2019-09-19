#include "consts.h"

#ifdef NDEBUG
#define UNIT_TEST  
#else
#define UNIT_TEST if (testSolveEquation()) {printf("Unit test failed\n"); return ERROR;} else { printf("Unit test ran succesfully\n");}  
#endif

int main() {

	UNIT_TEST

	double a, b, c, x1, x2;
	x1 = 0;
	x2 = 0;
	int roots = 0;
	a = NAN, b = NAN, c = NAN;
	printf("Square equation solver\n"
			"(c) Space kotik 2019\n\n");
	printf("Type the coefficients a, b and c:\n");
	scanf("%lf%lf%lf", &a, &b, &c);
	roots = solveEquation(a, b, c, &x1, &x2);
	printSol(x1, x2, roots);
	return 0;
}

int solveEquation(double a, double b, double c, double *x1, double *x2) {
	assert(isfinite(a));
	assert(isfinite(b));
	assert(isfinite(c));
	assert(x1 != NULL);
	assert(x2 != NULL);
	assert(x1 != x2);

	if (a == 0) {
		if (b == 0) {
			return (c == 0) ? INF_ROOTS : 0;
		}
		else {	//(b != 0)
			*x1 = *x2 = -c / b;
			return 1;
		}
	}
	else {	//(a != 0)
		double discr = b*b - 4*a*c;
		if (discr < 0)
			return 0;
		else {
			double loc = sqrt(discr);
			*x1 = (-b + loc) / (2*a);
			*x2 = (-b - loc) / (2*a);
			return (*x1 == *x2) ? 1 : 2;
		}
	}
}

void printSol(double x1, double x2, int roots) {
	assert (x1 != NAN);
	assert (x2 != NAN);
	assert (roots >= 0);

	switch (roots) {
		case 0:
			printf("No solutions\n");
			break;
		case 1:
			printf("x = %lg\n", x1);
			break;
		case 2:
			printf("x1 = %lg x2 = %lg\n", x1, x2);
			break;
		case INF_ROOTS:
			printf("Solution is any number\n");
			break;
		default:
			printf("ERROR!\n");
	}
}