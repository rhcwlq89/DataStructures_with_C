#include <stdio.h>
#include <stdbool.h>
#include "stackADT.h"

int main(void) {
	// Local Definitions
	bool done = false;
	int* dataPtr;
	int result;

	STACK* stack;

	// Statements
	// Create a stack and allocate memory for data
	stack = createStack();
	
	// Fill stack
	while (!done) {
		dataPtr = (int*)malloc(sizeof(int));
		printf("Enter a number: character to stop: ");
		result = scanf_s("%d", dataPtr);
		if(result == 0 || fullStack(stack))
			done = true;
		else 			
			pushStack(stack, dataPtr);
		printf("%d\n", result);
	} // while

	// Now print numbers in reverse
	printf("\n\nThe list of numbers reversed:\n");
	while (!emptyStack(stack)) {
		dataPtr = (int*)popStack(stack);
		printf("%3d\n", *dataPtr);
		free(dataPtr);
	} // while

	// Destroying Stack
	destroyStack(stack);
	return 0;
}