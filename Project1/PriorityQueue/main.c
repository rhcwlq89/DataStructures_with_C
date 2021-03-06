/*	Implement priority queue using heap.
*/
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "HeapADT.h"

// Construct Definitions
const int maxQueue = 20;

// Structure Declarations
typedef struct {
	int id;
	int priority;
	int serial;
} CUST;

// Prototype Declarations
int compareCust(void* cust1, void* cust2);
void processPQ(HEAP* heap);
char menu(void);
CUST* getCust(void);

int main(void) {
	// Local Definitions
	HEAP* prQueue;

	// Statements
	printf("Begin Priority Queue Demonstrations\n");

	prQueue = heapCreate(maxQueue, compareCust);
	processPQ(prQueue);

	printf("End Priority Queue Demonstration\n");
	return 0;
} // main

/*	comapare
	Compare priority of two customers to determine
	who has higher priority.
		Pre		Given two customer structures
		Post	if cust1	>	cust2	return +1
				if cust1	==	cust2	return +0
				if cust1	<	cust2	return -1
*/
int compareCust(void* cust1, void* cust2) {
	// Local Definitions
	CUST c1;
	CUST c2;

	// Statements
	c1 = *(CUST*)cust1;
	c2 = *(CUST*)cust2;

	if (c1.serial < c2.serial)
		return -1;
	else if (c1.serial == c2.serial)
		return 0;
	return +1;
} // compareCust

/*	processPQ
	Compare priority of two customers to determine
	who has higher priority.
		Pre		Given two customer structures
		Post	if	cust1	>	cust2	return +1
				if	cust1	==	cust2	return +0
				if	cust1	<	cust2	return -1
*/
void processPQ(HEAP* prQueue) {
	// Local Definitions
	CUST* cust;
	bool result;
	char option;
	int numCusts = 0;

	// Statements
	do {
		option = menu();
		switch (option) {
			case 'e':
				cust = getCust();
				numCusts++;
				cust->serial = cust->priority * 1000 + (1000 - numCusts);
				result = heapInsert(prQueue, cust);
				if (!result)
					printf("Error inserting into heap\n"), exit(100);
				break;
			case 'd':
				result = heapDelete(prQueue, (void**)&cust);
				if (!result)
					printf("Error: customer not found\n");
				else {
					printf("Customer %4d deleted\n", cust->id);
					numCusts--;
				} // else
		} // switch
	} while (option != 'q');

	return;
} // processPQ

/*	menu
	Display menu and get action.
		Pre		nothing
		Post	action read and validated
*/
char menu(void) {
	// Local Declarations
	char option;
	bool valid;

	// Statements
	printf("\n========== Menu ==========\n");
	printf(" e : Enter Customer Flight  \n");
	printf(" d : Delete Customer Flight \n");
	printf(" q : Quit.                  \n");
	printf("============================\n");
	printf("Please enter your choice:	");

	do {
		scanf_s("%c", &option);
		option = tolower(option);
		switch (option) {
			case 'e':
			case 'd':
			case 'q': 
				valid = true;
				break;
			default :
				printf("Invalid choice. Re-Enter: ");
				valid = false;
				break;
		} // switch
	} while (!valid);

	return option;
} // menu

/*	getCust
	Reads customer data from keyboard.
		Pre		nothing
		Post	data read and returned in structure
*/
CUST* getCust(void) {
	// Local Definitions
	CUST* cust;

	// Statements
	cust = (CUST*)malloc((sizeof(CUST)));
	if (!cust)
		printf("Memory overflow in getCust\n"), exit(200);

	printf("Enter customer id:		");
	scanf_s("%d", &cust->id);
	printf("Enter customer priority:");
	scanf_s("%d", &cust->priority);
	return cust;
} // getCust