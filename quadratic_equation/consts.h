#ifndef CONSTS_H
#define CONSTS_H

#include <stdio.h>
#include <math.h>
#include <assert.h>

#define INF_ROOTS 3
#define ERROR -1
#define OK 0
#define TOTAL_TESTS 4

#define NDEBUG

//! @file main.c

//! @mainpage
//! -main.c

//! doxygen

//!
//!
//! @param[in] a - 
//! @note


int solveEquation(double a, double b, double c, double *x1, double *x2);
void printSol(double x1, double x2, int solutions);
//int testSolveEquation (int testsCount, int (*testFunc)(int ));
//int tester(int testNum);
int tester(double a, double b, double c, double x1, double x2, int roots);
int testSolveEquation();

#endif