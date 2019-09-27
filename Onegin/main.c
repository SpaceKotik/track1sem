#include "consts.h"

int main(int argc, char *argv[]) {
	//setlocale(LC_ALL, "Rus");
	FILE *sourceTextFile;
	if (argc > 1)
		sourceTextFile = fopen(argv[1], "r");
	else
		sourceTextFile = fopen("Onegin.txt", "r");

	assert(sourceTextFile != NULL);

	const unsigned int textSizeChar = FindSize(sourceTextFile, CHARS);
	const unsigned int textSizeLines = FindSize(sourceTextFile, LINES);

	char *sourceText = (char*)malloc(textSizeChar+1);
	assert(sourceText != NULL);
	scanText(sourceTextFile, sourceText);
	fclose(sourceTextFile);

	char **defaultOrder = (char**)malloc(textSizeLines*sizeof(char*));
	assert(defaultOrder != NULL);
	setDefaultOrder(sourceText, defaultOrder, textSizeLines);

	char **firstToLastOrder = (char**)malloc(textSizeLines*sizeof(char*));
	assert(firstToLastOrder != NULL);
	setDefaultOrder(sourceText, firstToLastOrder, textSizeLines);

	char **LastToFirstOrder = (char**)malloc(textSizeLines*sizeof(char*));
	assert(LastToFirstOrder != NULL);
	setDefaultOrder(sourceText, LastToFirstOrder, textSizeLines);

	sortText(LastToFirstOrder, textSizeLines, LTOF);
	sortText(firstToLastOrder, textSizeLines, FTOL);


	FILE *outputTextFile = fopen("Onegin_sorted.txt", "w");
	assert(outputTextFile != NULL);

	WriteToFile(sourceText, outputTextFile, defaultOrder, textSizeLines);

	int i;
	for (i = 0; i < 20; ++i) {
		fprintf(outputTextFile, "-");
	}
	fprintf(outputTextFile, "\n");

	WriteToFile(sourceText, outputTextFile, firstToLastOrder, textSizeLines);

	for (i = 0; i < 20; ++i) {
		fprintf(outputTextFile, "-");
	}
	fprintf(outputTextFile, "\n");

	WriteToFile(sourceText, outputTextFile, LastToFirstOrder, textSizeLines);

	fclose(outputTextFile);

	free(sourceText);
	free(defaultOrder);
	free(firstToLastOrder);
	printf("Sorting done\n");
	return 0;
}

unsigned int FindSize(FILE *sourceFile, const int mode) {
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
	outText[i] = '\0';
	return SUCCESS;
}

int setDefaultOrder(char *sourceText, char **order, const unsigned Lines) {
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

int WriteToFile(char *sourceText, FILE* file, char **order, const unsigned int lines) {
	assert(sourceText != NULL);
	assert(file != NULL);
	assert(order != NULL);

	int i;
	for (i = 0; i < lines; ++i) {
		int j = -1;
		do {
			fprintf(file, "%c", order[i][++j]);
		} while (order[i][j] != '\n');
	}
	return SUCCESS;
}