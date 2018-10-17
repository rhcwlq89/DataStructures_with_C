#pragma once
#include <stdlib.h>
#include <stdbool.h>

// Stasck ADT Type Definitions
typedef struct node {
	void* dataPtr;
	struct node* link;
} STACK_NODE;

typedef struct {
	int count;
	STACK_NODE* top;
} STACK;

//Prototype Declarations
STACK* createStack(void);
STACK* destroyStack(STACK* stack);

bool pushStack(STACK* stack, void* dataInPtr);
void* popStack(STACK* stack);
void* stackTop(STACK* stack);
int stackCount(STACK* stack);

bool emptyStack(STACK* stack);
bool fullStack(STACK* stack);

/*	createStack
	This algorithm creates an empty stack.
		Pre Nothing
		Post Returns pointer to a null stack
				-or- NULL if overflow
*/
STACK* createStack(void) {
	//Local Definitions
	STACK* stack;

	// Statements
	stack = (STACK*)malloc(sizeof(STACK));
	if (stack) {
		stack->count = 0;
		stack->top = NULL;
	} // if

	return stack;
} // createStack

/*	pushStack
	This function pushes an item onto the stack.
		Pre		stack is a pointer to the stack
				dataPtr pointer to data to be inserted
		Post	Data inserted into stack
		Return	true if successful
				false if underflow
*/
bool pushStack(STACK* stack, void* dataInPtr) {
	//Local Definitions
	STACK_NODE* newPtr;

	// Statements
	newPtr = (STACK_NODE*)malloc(sizeof(STACK_NODE));
	if (!newPtr) {
		return false;
	}

	newPtr->dataPtr = dataInPtr;

	newPtr->link = stack->top;
	stack->top = newPtr;

	(stack->count)++;
	return true;
} // pushStack

/*	popStack
	This function pops item on the top of the stack.
		Pre		stack is pointer to a stack
		Post	Returns pointer to user data if successful
				NULL if underflow
*/
void* popStack(STACK* stack) {
	//Local Definitions
	void* dataOutPtr;
	STACK_NODE* temp;

	//Statements
	if (stack->count == 0)
		dataOutPtr = NULL;
	else {
		temp = stack->top;
		dataOutPtr = stack->top->dataPtr;
		stack->top = stack->top->link;
		free(temp);
		(stack->count)--;
	} // else

	return dataOutPtr;
} // popStack

/*	stackTop
	Retrieves data from the top of stack without
	changing the stack.
		Pre		stack is a pointer to the stack
		Post	Returns data pointer if successful
						null pointer if stack empty
*/
void* stackTop(STACK* stack) {
	//Statements
	if (stack->count == 0)
		return NULL;
	else
		return stack->top->dataPtr;
} // stackTop

/*	emptyStack
	This function determines if a stack is empty.
		Pre		stack is pointer to a stack
		Post	returns 1 if empty; 0 if data in stack
*/
bool emptyStack(STACK* stack) {
	//Statements
	return (stack->count == 0);
} // emptyStack

/*	fullStack
	This function determines if a stack is full.
	Full is defined as heap full.
		Pre		stack is pointer to a stack head node
		Return	true if heap full
				false if heap has room
*/
bool fullStack(STACK* stack) {
	//Local Definitions
	STACK_NODE* temp;

	//Statements
	if ((temp = (STACK_NODE*)malloc(sizeof(*(stack->top))))) {
		free(temp);
		return false;
	} // if

	// malloc failed
	return true;
} // fullStack

/*	stackCount
	Returns number of elements in stack
		Pre		stack is a pointer to the stack
		Post	count returned
*/
int stackCount(STACK* stack) {
	//Statements
	return stack->count;
} // stackCount

/*	destroyStack
	This function release all nodes to the heap.
		Pre		A stack
		Post	returns null pointer
*/
STACK* destroyStack(STACK* stack) {
	//Local Definitions
	STACK_NODE* temp;

	//Statements
	if (stack) {
		//Delete all nodes in stack
		while (stack->top != NULL) {
			//Delete all nodes in stack
			free(stack->top->dataPtr);

			temp = stack->top;
			stack->top = stack->top->link;
			free(temp);
		} // while

		// Stack now empty. Destroy stack head node.
		free(stack);
	} // if stack
} //destroyStack