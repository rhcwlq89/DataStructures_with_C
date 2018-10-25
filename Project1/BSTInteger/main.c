#include <stdio.h>
#include <stdlib.h>
#include "BinarySearchTreeADT.h"

// Prototype Declarations
int compareInt(void* num1, void* num2);
void printBST(void* num1);

int main(void) {
	// Local Definitions
	BST_TREE* BSTRoot;
	int* dataPtr;
	int dataIn = +1;

	// Statements
	printf("Begin BST Demonstation\n");
	BSTRoot = BST_Create(compareInt);

	// BuildTree
	printf("Enter a list of positive integers;\n");
	printf("Enter a negative to stop.\n");

	do {
		printf("Enter a number: ");
		scanf_s("%d", &dataIn);
		if (dataIn > -1) {
			dataPtr = (int*)malloc(sizeof(int));
			if (!dataPtr) {
				printf("Memory Overflow in add\n"), exit(100);
			} // if overflow

			*dataPtr = dataIn;
			BST_Insert(BSTRoot, dataPtr);
		} // valid data
	} while (dataIn > -1);

	printf("\nBST countains:\n");
	BST_Traverse(BSTRoot, printBST);

	printf("\nEnd BST Deomostration\n");
	return 0;
} // main

/*	compareInt
	Compare two integers and return low, equal, high.
		Pre		num1 and num2 are valid pointers to integers
		Post	return low(-1), equal(0), or high(+1)
*/
int compareInt(void* num1, void* num2) {
	// Local Definitions
	int key1;
	int key2;

	// Statements
	key1 = *(int*)num1;
	key2 = *(int*)num2;

	if (key1 < key2)
		return -1;
	if (key1 == key2)
		return 0;
	return +1;
} // compareInt

/*	printBST
	Print one integer from BST.
		Pre		num1 is a pointer to an integer
		Post	integer printed and line advanced
*/
void printBST(void* num1) {
	// Statements
	printf("%4d\n", *(int*)num1);
	return;
}


