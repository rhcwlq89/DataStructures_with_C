/*	This program is a test driver to demonstrate the basic
	operation of the stack push and pop functions.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct Declarations
typedef struct node {
	char	data;
	struct node* link;
} STACK_NODE;

// Prototype Declarations
void insertData(STACK_NODE** pStackTop);
void print(STACK_NODE** pStackTop);

bool push(STACK_NODE** pList, char dataIn);
bool pop(STACK_NODE** pList, char* dataOut);

int main(void) {
	// Local Definitions
	STACK_NODE* pStackTop;

	// Stackments
	printf("Beginning Simple Stack Program\n\n");

	pStackTop = NULL;
	insertData(&pStackTop);
	print(&pStackTop);

	printf("\n\nEnd Simple Stack Program\n");
	return 0;
} // main

/*	insertData
	This program creates random character data and
	inserts them into a linked list stack.
		Pre		pStackTop is a pointer to first node
		Post	Stack has been created
*/
void insertData(STACK_NODE** pStackTop) {
	// Local Definitions
	char charIn;
	bool success;

	// Statements
	printf("Creating charaters: ");
	for (int nodeCount = 0; nodeCount < 10; nodeCount++) {
		// Generate uppercase character
		charIn = rand() % 26 + 'A';
		printf("%c", charIn);
		success = push(pStackTop, charIn);
		if (!success) {
			printf("Error 100: Out of Memory\n");
			exit(100);
		} // if
	} // for

	printf("\n");
	return;
} // insertData

/*	push
	Inserts node into linked list stack.
		Pre		pStackTop is pointer to valid stack
		Post	charIn inserted
		Return	true if successful
				false if underflow
*/
bool push(STACK_NODE** pStackTop, char charIn) {
	// Local Definitions
	STACK_NODE* pNew;
	bool success;

	// Statements
	pNew = (STACK_NODE*)malloc(sizeof(STACK_NODE));
	if (!pNew)
		success = false;
	else {
		pNew->data = charIn;
		pNew->link = *pStackTop;
		*pStackTop = pNew;
		success = true;
	} // else

	return success;
} // push

/*	print
	This function prints a singly linked stack.
		Pre		pStackTop is pointer to valid stack
		Post	data in stack printed
*/
void print(STACK_NODE** pStackTop) {
	// Local Definitions 
	char printData;

	// Statements
	printf("Stack contained:	");
	while (pop(pStackTop, &printData))
		printf("%c", printData);
	return;
} // print

/*	pop
	Delete node from linked list stack.
		Pre		pStackTop is pointer to valid stack
		Post	charOut contains deleted data
		Return	true if successful
				false if underflow
*/
bool pop(STACK_NODE** pStackTop, char* charOut) {
	// Local Definitions
	STACK_NODE* pDlt;
	bool success;

	// Statements
	if (*pStackTop) {
		success = true;
		*charOut = (*pStackTop)->data;
		pDlt = *pStackTop;
		*pStackTop = (*pStackTop)->link;
		free(pDlt);
	} // if
	else
		success = false;
	return success;
} // pop