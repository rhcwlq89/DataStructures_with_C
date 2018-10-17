/*	This program evaluates a postfix expression and
	returns its value. The postfix expression must be
	valid with each operand being only one digit.
*/
#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"

// Prototype Declarations
bool isOperator(char token);
int calc(int operand1, char oper, int operand2);

int main(void) {
	// Local Definitions
	char token;
	int operand1;
	int operand2;
	int value;
	int* dataPtr;
	STACK* stack;

	// Statements
	// Create Stack
	stack = createStack();

	// read postfix expression, char by char
	printf("Input formula : ");
	while ((token = getchar()) != '\n') {
		if (!isOperator(token)) {
			dataPtr = (int*)malloc(sizeof(int));
			*dataPtr = atoi(&token);
			pushStack(stack, dataPtr);
		} // if
		else {
			// character is operand
			dataPtr = (int*)popStack(stack);
			operand2 = *dataPtr;
			dataPtr = (int*)popStack(stack);
			operand1 = *dataPtr;
			value = calc(operand1, token, operand2);
			dataPtr = (int*)malloc(sizeof(int));
			*dataPtr = value;
			pushStack(stack, dataPtr);
		} // else
	} // while

	// The final result is in stack. Pop it print it
	dataPtr = (int*)popStack(stack);
	value = *dataPtr;
	printf("The result is : %d\n", value);

	// Now destroy the stack
	destroyStack(stack);
	return 0;
}

/*	isOperator
	Validate operator.
		Pre		token is operator to be validated
		Post	return true if valid, false if not
*/
bool isOperator(char token) {
	// Statements
	if (token == '*' || token == '/' || token == '+' || token == '-') {
		return true;
	}
	return false;
} // isOperator

/*	calc
	Given two values and operator, determine value of formula.
		Pre		operand1 and operand2 are values
				oper is the operator to be used
		Post	return result of calculation
*/
int calc(int operand1, char oper, int operand2) {
	// Local Declaration
	int result;

	// Statements
	switch (oper) {
		case '+': result = operand1 + operand2;
			break;
		case '-': result = operand1 - operand2;
			break;
		case '*': result = operand1 * operand2;
			break;
		case '/': result = operand1 / operand2;
			break;
	} // switch

	return result;
} // calc