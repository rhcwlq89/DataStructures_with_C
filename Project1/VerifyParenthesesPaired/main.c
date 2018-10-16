/*	This program reads a source program and parses it to
	make sure all opening-closing parentheses are paired.
*/
#include <stdio.h>
#include "stackADT.h"

// Error Messages
const char closMiss[] = "Close paren missing at line";
const char openMiss[] = "Open paren missing at line";

int main(void) {
	// Local Definitions
	STACK* stack;
	char token;
	char* dataPtr;
	char fileID[25];
	FILE* fpIn;
	int lineCount = 1;

	// Statements
	// CreateStack
	stack = createStack();
	printf("Enter file ID for file to be parsed : ");
	scanf_s("%s", fileID, sizeof(fileID));

	fopen_s(&fpIn, fileID, "r");
	if (!fpIn)
		printf("Error opening %s\n", fileID), exit(100);

	// read characters from the source code and parse
	while ((token = fgetc(fpIn)) != EOF) {
		if (token == '\n')
			lineCount++;
		if (token == '(') {
			dataPtr = (char*)malloc(sizeof(char));
			pushStack(stack, dataPtr);
		} // if
		else {
			if (token == ')') {
				if (emptyStack(stack)) {
					printf("%s %d\n", openMiss, lineCount);
					return 1;
				} // if true
				else {
					popStack(stack);
				} // else
			} // token ==
		} // while
	} // while

	if (!emptyStack(stack)) {
		printf("%s %d\n", closMiss, lineCount);
		return 1;
	} // if

	// Now destroy the stack
	destroyStack(stack);
	printf("Parsing is OK: %d Lines parsed.\n", lineCount);
	return 0;
} // main