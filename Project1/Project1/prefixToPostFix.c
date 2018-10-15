#include <stdio.h>
#include <string.h>

#define OPERATORS "+-*/"

// ProtoType Declarations
void preToPostFix(char* preFixIn, char* exprOut);
int findExprLen(char* exprLn);

int main(void) {
	// Local Definitions
	char preFixExpr[256] = "-+*ABC/EF";
	char postFixExpr[256] = "";

	// Statements
	printf("Begin prefix to postfix conversion\n\n");

	preToPostFix(preFixExpr, postFixExpr);
	printf("Prefix expr : %-s\n", preFixExpr);
	printf("PostFix expr : %-s\n", postFixExpr);

	printf("\nEnd prefix to postfix conversion\n");
	return 0;
} // main

/*	preToPostFix
	Convert prefix expression to postfix format.
		Pre		preFixIn is string prefix expression.
				expresson can contain no errors/spaces
				portFix is string variable for postfix
		Post	expression has been converted.
*/
void preToPostFix(char* preFixIn, char* postFix) {
	// Local Definitions
	char operator1[2];
	char postFix1[256];
	char postFix2[256];
	char temp[256];
	int lenPreFix;

	printf("Prefix expr : %-s\n", preFixIn);
	printf("PostFix expr : %-s\n", postFix);

	// Statements
	if (strlen(preFixIn) == 1) {
		*postFix = *preFixIn;
		*(postFix + 1) = '\0';
		return;
	} // if only operand

	*operator1 = *preFixIn;
	*(operator1 + 1) = '\0';

	// Find first expression
	lenPreFix = findExprLen(preFixIn + 1);
	strncpy_s(temp, 256, preFixIn + 1, lenPreFix);
	*(temp + lenPreFix) = '\0';
	preToPostFix(temp, postFix1);

	// Find second expression
	strcpy_s(temp, 256, preFixIn + 1 + lenPreFix);
	preToPostFix(temp, postFix2);

	printf("postFix1 expr : %-s\n", postFix1);
	printf("postFix2 expr : %-s\n", postFix2);

	// Concatenate to postFix
	strcpy_s(postFix, 256, postFix1);
	strcat_s(postFix, 256, postFix2);
	strcat_s(postFix, 256, operator1);

	return;
} // preToPostFix

/*	findExprLen
	Determine size of first substring in an expression.
		Pre		exprIn contains prefix expression
		Post	size of expression is returned
*/
int findExprLen(char* exprIn) {
	// Local Definitions
	int len1;
	int len2;

	// Statements
	if (strcspn(exprIn, OPERATORS) == 0) {
		// General Case : First character is operator
		// Find length of first expression
		len1 = findExprLen(exprIn + 1);
		// Find length of second expression
		len2 = findExprLen(exprIn + 1 + len1);
	} // if
	else {
		// Base-case -- first char is operand
		len1 = len2 = 0;
	}

	return len1 + len2 + 1;
} // findExprLen
