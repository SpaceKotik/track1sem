//--------------------------------------------------------------------------------------------
//! @author SpaceKotik
//! @file	main.c
//! Main file of the project.
//!
//! This file contains functions for sorting poems.
//--------------------------------------------------------------------------------------------

#include "consts.h"

//--------------------------------------------------------------------------------------------
//! @fn main
//! Main function of project.
//--------------------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
	//setlocale(LC_ALL, "Rus");
	FILE *sourceTextFile;
	if (argc > 1)
		sourceTextFile = fopen(argv[1], "r");
	else
		sourceTextFile = fopen("Onegin.txt", "r");

	assert(sourceTextFile != NULL);

	const unsigned int textSizeChar = findSize(sourceTextFile, CHARS);
	const unsigned int textSizeLines = findSize(sourceTextFile, LINES);

	char *sourceText = (char*)malloc(textSizeChar+1);
	assert(sourceText != NULL);
	scanText(sourceTextFile, sourceText);
	fclose(sourceTextFile);

	char **defaultOrder = (char**)malloc(textSizeLines*sizeof(char*));
	assert(defaultOrder != NULL);
	setDefaultOrder(sourceText, defaultOrder);

	char **firstToLastOrder = (char**)malloc(textSizeLines*sizeof(char*));
	assert(firstToLastOrder != NULL);
	setDefaultOrder(sourceText, firstToLastOrder);

	char **LastToFirstOrder = (char**)malloc(textSizeLines*sizeof(char*));
	assert(LastToFirstOrder != NULL);
	setDefaultOrder(sourceText, LastToFirstOrder);

	sortText(LastToFirstOrder, textSizeLines, LTOF);
	sortText(firstToLastOrder, textSizeLines, FTOL);


	FILE *outputTextFile = fopen("Onegin_sorted.txt", "w");
	assert(outputTextFile != NULL);

	WriteToFile(outputTextFile, defaultOrder, textSizeLines);

	int i;
	for (i = 0; i < 20; ++i) {
		fprintf(outputTextFile, "-");
	}
	fprintf(outputTextFile, "\n");

	WriteToFile(outputTextFile, firstToLastOrder, textSizeLines);

	for (i = 0; i < 20; ++i) {
		fprintf(outputTextFile, "-");
	}
	fprintf(outputTextFile, "\n");

	WriteToFile(outputTextFile, LastToFirstOrder, textSizeLines);

	fclose(outputTextFile);

	free(sourceText);
	free(defaultOrder);
	free(firstToLastOrder);
	printf("Sorting done\n");
	return 0;
}

//--------------------------------------------------------------------------------------------
//! @fn findSize(FILE *sourceFile, const int mode)
//! Finds size of the input file in *mode* value.
//!
//! @param[in]  sourceText  Measurable file.
//! @param[in]  mode		Defines what the function is measuring (CHARS or LINES).
//!
//! @return		Returns size or -1 in case of error.
//--------------------------------------------------------------------------------------------

unsigned int findSize(FILE *sourceFile, const int mode) {
	assert(sourceFile != NULL);

	fseek(sourceFile, 0, SEEK_SET);
	unsigned int totalSize = 0;
	char a = 'a';
	switch (mode) {
		case CHARS:
			while(fscanf(sourceFile, "%c", &a) != EOF) {
				totalSize++;
			};
			break;
		case LINES:
			while(fscanf(sourceFile, "%c", &a) != EOF) {
				if (a == '\n')
					totalSize++;
			};
			break;
		default:
			return ERROR;
			break;
	}
	return totalSize;
}

//--------------------------------------------------------------------------------------------
//! @fn scanText(FILE *sourceFile, char *outText)
//! Writes all text from the sourceFile to string outText.
//!
//! @param[in]  sourceText 	Readable file.
//! @param[out]	outText 	String in which the text is written.
//!
//! @return		Returns 0 on success or -1 on error.
//--------------------------------------------------------------------------------------------

int scanText(FILE *sourceFile, char *outText) {
	assert(sourceFile != NULL);
	assert(outText != NULL);

	if (SUCCESS != fseek(sourceFile, 0, SEEK_SET))
		return ERROR;
	int i = 0;
	char currChar;
	while (fscanf(sourceFile, "%c", &currChar) != EOF) {
		outText[i++] = currChar;
	}
	//fread(sourceFile, )
	outText[i] = '\0';
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------
//! @fn setDefaultOrder(char *sourceText, char **order)
//! Sets the default otder of lines (1, 2, 3...).
//!
//! @param[in] 	sourceText 	Readable string.
//! @param[out]	order 		The array of pointers to the beginning of the lines.
//!
//! @return		Always returns 0 (for now at least).
//--------------------------------------------------------------------------------------------


int setDefaultOrder(char *sourceText, char **order) {
	assert(sourceText != NULL);
	assert(order != NULL);

	int i = 0;
	int j = 0;
		order[i++] = sourceText;
		while (sourceText[j] != '\0') {
			if (sourceText[j-1] == '\n') {
				order[i++] = (sourceText + j);
			}
			j++;
		}
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------
//! @fn sortText(char **order, const unsigned int lines, const int mode)
//! Sorts the array of pointers to beginnings of the lines using qsort.
//!
//!
//! @param[out] order 	The array of pointers to the beginning of the lines.
//! @param[in] lines 	The number of lines in the text.
//! @param[in]	mode 	FTOL or LTOF; defines the order of sorting.	 
//!
//! @return				Returns 0 on success or -1 on error.
//--------------------------------------------------------------------------------------------

int sortText(char **order, const unsigned int lines, const int mode) {
	assert(order != NULL);

	switch(mode) {
		case FTOL:
			qsort(order, lines, sizeof(char*), compFtoL);
			break;
		case LTOF:
			qsort(order, lines, sizeof(char*), compLtoF);
			break;
		default:
			return ERROR;
			break;
	}
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------
//! @fn compFtoL(const void *first, const void *second)
//! Comparator for qsort; sorts strings from firts to last letter.
//!
//!
//! @param[in] 	first 	The first string.
//! @param[in]	second	The second string.	 
//!
//! @return				-1, 0 or 1 if 1st string is less, equal to or greater than 2nd string.
//--------------------------------------------------------------------------------------------

int compFtoL(const void *first, const void *second) {
	char *frst = *(char**)first;
	char *scnd = *(char**)second;
	int i1 = 0;
	int i2 = 0;
	while(1) {
		if (frst[i1] == '\n' && scnd[i2] == '\n')
			return 0;
		if (frst[i1] == '\n')
			return -1;
		if (scnd[i2] == '\n')
			return 1;

		if (!isalpha(frst[i1]) && (frst[i1] != '\n')) {
			i1++;
			continue;
		}
		if (!isalpha(scnd[i2]) && (scnd[i2] != '\n')) {
			i2++;
			continue;
		}

		if (tolower(frst[i1]) < tolower(scnd[i2]))
			return -1;
		else if (tolower(frst[i1]) > tolower(scnd[i2]))
			return 1;
		else if (tolower(frst[i1]) == tolower(scnd[i2])) {
			i1++;
			i2++;
			continue;
		}
	}
}

//--------------------------------------------------------------------------------------------
//! @fn compLtoF(const void *first, const void *second)
//! Comparator for qsort; sorts strings from last to first letter.
//!
//!
//! @param[in] 	first 	The first string.
//! @param[in]	second	The second string.	 
//!
//! @return				-1, 0 or 1 if 1st string is less, equal to or greater than 2nd string.
//--------------------------------------------------------------------------------------------

int compLtoF(const void *first, const void *second) {
	char *frst = *(char**)first;
	char *scnd = *(char**)second;

	int i1 = 0;
	int i2 = 0;

	while (frst[i1] != '\n') {
		i1++;
	}
	i1--;
	while (scnd[i2] != '\n') {
		i2++;
	}
	i2--;

	while(1) {
		if (i1 <= 0 && i2 <= 0)
			return 0;
		else if (i1 <= 0)
			return -1;
		else if (i2 <= 0)
			return 1;

		if (!isalpha(frst[i1]) && (i1 != 0)) {
			i1--;
			continue;
		}
		if (!isalpha(scnd[i2]) && (i2 != 0)) {
			i2--;
			continue;
		}

		if (tolower(frst[i1]) == tolower(scnd[i2])) {
			i1--;
			i2--;
			continue;
		}
		else if (tolower(frst[i1]) > tolower(scnd[i2]))
			return 1;
		else if (tolower(frst[i1]) < tolower(scnd[i2]))
			return -1;
	}
}

//--------------------------------------------------------------------------------------------
//! @fn WriteToFile(FILE* file, char **order, const unsigned int lines)
//! Writes a poem to file.
//!
//!
//! @param[in] 	file 	The destination file.
//! @param[in]	order	The array of pointers to the beginning of the lines.
//! @param[in]	lines	The number of lines in the text.	
//!
//! @return				Always returns 0 (for now at least).
//--------------------------------------------------------------------------------------------

int WriteToFile(FILE* file, char **order, const unsigned int lines) {
	assert(file != NULL);
	assert(order != NULL);

	int i;
	for (i = 0; i < lines; ++i) {
		int j = -1;
		do {
			fprintf(file, "%c", order[i][++j]);
		} while (order[i][j] != '\n');
	}

	/*int i;
	for (i = 0; i < lines; ++i) {
			fprintf(file, "%s", order[i]);
	}*/	
	return SUCCESS;
}