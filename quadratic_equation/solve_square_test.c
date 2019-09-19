#include "consts.h"
/*double tests [][6] =
{
	{0, 0, 0, 0, 0, INF_ROOTS}, // {a, b, c, x1, x2, rootsNum}
	{0, 1, 0, 0, 0, 1},
	{0, 0, 1, 0, 0, 0},
	{1, 0, 0, 0, 0, 1}
};
*/

/*int tester(int testNum) {
	double x1 = 0, x2 = 0;
	int roots = -1;
	roots = solveEquation(tests[testNum][0], tests[testNum][1], tests[testNum][2], &x1, &x2);
	if (roots == tests[testNum][5] && x1 == tests[testNum][3] && x2 == tests[testNum][4])
		return OK;
	else {
		printf("Error in test #%d\n"
				"a = %lg, b = %lg, c = %lg\n"
				"Expected: x1 = %lg, x2 = %lg, roots = %lg\n"
				"Actually: x1 = %lg, x2 = %lg, roots = %d\n\n", testNum + 1, tests[testNum][0], tests[testNum][1], tests[testNum][2],
												tests[testNum][3], tests[testNum][4], tests[testNum][5], x1, x2, roots);
		return ERROR;
	}
}
*/
int tester(double a, double b, double c, double x1, double x2, int roots) {
	double x1_loc = 0, x2_loc = 0;
	int roots_loc = -1;
	roots_loc = solveEquation(a, b, c, &x1_loc, &x2_loc);
	if (roots_loc == roots && x1 == x1_loc && x2 == x2_loc)
		return OK;
	else {
		/*printf("Error!\n"
				"a = %lg, b = %lg, c = %lg\n"
				"Expected: x1 = %lg, x2 = %lg, roots = %lg\n"
				"Actually: x1 = %lg, x2 = %lg, roots = %d\n\n", testNum + 1, tests[testNum][0], tests[testNum][1], tests[testNum][2],
												tests[testNum][3], tests[testNum][4], tests[testNum][5], x1, x2, roots);
		
		*/
		return ERROR;
	}
}

//#define UNITTEST((x), (cond), (y)) 
#define UNITTEST_SOLVE_EQUATION(a, b, c, x1, x2, roots) if (tester(a, b, c, x1, x2, roots) == ERROR) return ERROR

int testSolveEquation()
{
	UNITTEST_SOLVE_EQUATION(0, 1, 0, 0, 0, 1);
	return OK;
}