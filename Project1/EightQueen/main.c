/*	This program tests the eight queens algorithm. Eight
	queens is a classic chess problem in which eight
	queens are placed on a chess board in positions such
	that no queen can capture another queen.
*/
#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"

// Structure Declarations
typedef struct {
	int row;
	int col;
} POSITION;

// Prototype Declarations
int getSize(void);

void fillBoard(STACK* stack, int boardSize);
void printBoard(STACK* stack, int boardSize);

bool guarded(int board[][9], int row, int col, int boardSize);

int main(void) {
	// Local Definitions
	int boardSize;
	
	STACK* stack;

	// Statements
	boardSize = getSize();
	stack = createStack();

	fillBoard(stack, boardSize);
	printBoard(stack, boardSize);
	destroyStack(stack);

	printf("\nWe hope you enjoyed Eight Queens.\n");
	return 0;
} // main

/*	getSize
	Prompt user for a valid board size.
		Pre		nothing
		Post	valid board size returned
*/
int getSize(void) {
	// Local Definitions
	int boardSize;

	// Statements
	printf("Welcome to Eight Queens. You may select\n"
		"a board size from 4 x 4 to 8 x 8. I will\n"
		"then position a queen in each row of the\n"
		"board so no queen may capture another\n"
		"queen. Note: There are no solutions for \n"
		"boards less than 4 x 4.\n");
	printf("\nPlease enter the board size: ");
	scanf_s("%d", &boardSize);
	while (boardSize < 4 || boardSize > 8) {
		printf("Board size must be greater than 3 \n"
			"and less than 9. You entered %d.\n"
			"Please re-enter. Thank you. \a\a\n\n"
			"Your board size: ", boardSize);
		scanf_s("%d", &boardSize);
	} // while
	return boardSize;
} // getSize

/*	fillBoard
	Position chess queens on game board so that no queen
	can capture any other queen.
		Pre		boardSize number of rows & columns on board
		Post	Queens' positions filled
*/
void fillBoard(STACK* stack, int boardSize) {
	// Local Definitions
	int row;
	int col;
	int board[9][9] = { 0 };	// 0 no queen : 1 queen
								// row 0 & col 0 not used
	POSITION* pPos;

	// Statements
	row = 1;
	col = 0;

	while (row <= boardSize) {
		while (col <= boardSize && row <= boardSize) {
			col++;
			if (!guarded(board, row, col, boardSize)) {
				board[row][col] = 1;

				pPos = (POSITION*)malloc(sizeof(POSITION));
				pPos->row = row;
				pPos->col = col;

				pushStack(stack, pPos);

				row++;
				col = 0;
			} // if
			
			while (col >= boardSize) {
				pPos = popStack(stack);
				row = pPos->row;
				col = pPos->col;
				board[row][col] = 0;
				free(pPos);
			} // while col
		} // while col
	} // while row

	return;
}

/*	guarded
	Checks rows, columns, diagonals for guarding queens
		Pre		board contains current positions for queens
				chkRow & chkCol are position for new queen
				boardSize is number of rows & cols in board
		Post	returns true if guarded; false if not
*/
bool guarded(int board[][9], int chkRow, int chkCol, int boardSize) {
	// Local Definitions
	int row;
	int col;

	// Statements
	// Check current col for a queen
	col = chkCol;
	for (row = 1; row <= chkRow; row++)
		if (board[row][col] == 1)
			return true;

	// Check diagonal right-up
	for (row = chkRow - 1, col = chkCol + 1; row > 0 && col <= boardSize; row--, col++)
		if (board[row][col] == 1)
			return true;

	// Check diagonal left-up
	for (row = chkRow - 1, col = chkCol - 1; row > 0 && col > 0; row--, col--)
		if (board[row][col] == 1)
			return true;

	return false;
} // guarded

/*	printBoard
	Print positions of chess queens on a game board
		Pre		stack contains positions of queen
				boardSize is the number of rows and columns
		Post	Queens' positions printed
*/
void printBoard(STACK* stack, int boardSize) {
	// Local Definitions
	int col;

	POSITION* pPos;
	STACK* pOutStack;

	// Statements
	if (emptyStack(stack)) {
		printf("There are no positions on this board\n");
		return;
	} // if

	printf("\nPlace queens in following position:\n");

	// Reverse stack for printing
	pOutStack = createStack();
	while (!emptyStack(stack)) {
		pPos = popStack(stack);
		pushStack(pOutStack, pPos);
	} // while

	// Now print board
	while (!emptyStack(pOutStack)) {
		pPos = popStack(pOutStack);
		printf("Row %d-Col %d: \t|", pPos->row, pPos->col);
		for (col = 1; col <= boardSize; col++) {
			if (pPos->col == col)
				printf(" Q |");
			else
				printf("   |");
		} // for
		printf("\n");
	} // while

	destroyStack(pOutStack);
	return;
}