#ifndef CONSTS_H
#define CONSTS_H

//#define NDEBUG

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <locale.h>
#include <ctype.h>

#define FTOL 1
#define LTOF 2
#define CHARS 1
#define LINES 2
#define SUCCESS 0
#define ERROR -1
#define ERROR_FILE -2


unsigned int findSize(FILE *SourceFile, const int mode);
int scanText(FILE *sourceFile, char *outText);
int setDefaultOrder(char *sourceText, char **order);
int sortText(char **Order, const unsigned int lines, const int mode);
int WriteToFile(FILE* file, char **Order, const unsigned int Lines);
int compFtoL(const void *frst, const void *scnd);
int compLtoF(const void *frst, const void *scnd);

#endif