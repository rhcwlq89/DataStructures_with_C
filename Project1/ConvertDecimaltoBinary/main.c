/*	This program reads an integer from the keyboard
	and prints its binary equivalent. It uses a stack
	to reverse the order of 0s and 1s produced.
*/
#include <stdio.h>
#include "stackADT.h"

int main(void) {
	// Local Definitions
	unsigned int num;
	int* digit;
	STACK* stack;

	// Statements
	// Create Stack
	stack = createStack();

	// prompt and read a number
	printf("Enter an integer : ");
	scanf_s("%d", &num);

	// create 0s and 1s and push them into the stack
	while (num > 0) {
		digit = (int*)malloc(sizeof(int));
		*digit = num % 2;
		pushStack(stack, digit);
		num = num / 2;
	} // while

	// Binary number created. Now print it
	printf("The binary number is : ");
	while (!emptyStack(stack)) {
		digit = (int*)popStack(stack);
		printf("%1d", *digit);
	} // while
	printf("\n");

	// Destorying Stack
	destroyStack(stack);
	return 0;
} // main