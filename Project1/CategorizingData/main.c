/*	Groups numbers into four groups using four gueues.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queueADT.h"

// Prototype Statements
void fillQueues(QUEUE*, QUEUE*, QUEUE*, QUEUE*);
void printQueues(QUEUE*, QUEUE*, QUEUE*, QUEUE*);

void printOneQueue(QUEUE* pQueue);

int main(void) {
	// Local Definitions
	QUEUE* q0to9;
	QUEUE* q10to19;
	QUEUE* q20to29;
	QUEUE* qOver29;

	// Statements
	printf("Welcome to a demonstration of categorizing\n"
		"data. We generate 25 random numbers and then\n"
		"group them into categories using queues.\n\n");

	q0to9 = createQueue();
	q10to19 = createQueue();
	q20to29 = createQueue();
	qOver29 = createQueue();

	fillQueues(q0to9, q10to19, q20to29, qOver29);
	printQueues(q0to9, q10to19, q20to29, qOver29);

	return 0;
} // main

/*	fillQueues
	This function generates data using rand() and
	places them in one of four gueues.
		Pre		All four queues have been created
		Post	Queues filled with data
*/
void fillQueues(QUEUE* q0to9, QUEUE* q10to19, QUEUE* q20to29, QUEUE* qOver29) {
	// Local Definitions
	int category;
	int item;
	int* dataPtr;

	// Statements
	printf("Categorizing data:\n");
	srand(79);

	for (int i = 1; i <= 25; i++) {
		if(!(dataPtr=(int*) malloc(sizeof(int)))) 
			printf("Overflow in fillQueues\a\n"), exit(100);

		*dataPtr = item = rand() % 51;
		category = item / 10;
		printf("%3d", item);
		if (!(i % 11))
			// Start new line when line full
			printf("\n");

		switch (category) {
			case 0: enqueue(q0to9, dataPtr);
				break;
			case 1: enqueue(q10to19, dataPtr);
				break;
			case 2: enqueue(q20to29, dataPtr);
				break;
			default: enqueue(qOver29, dataPtr);
				break;
		} // switch
	} // for

	printf("\nEnd of data categorization\n\n");
	return;
} // fillQueues

/*	printQueues
	This function prints the data in each of the queues.
		Pre		Queue have been filled
		Post	Data printed and dequeued
*/
void printQueues(QUEUE* q0to9, QUEUE* q10to19, QUEUE* q20to29, QUEUE* qOver29) {
	// Statements
	printf("Data	0.. 9 :");
	printOneQueue(q0to9);

	printf("Data	10..19 :");
	printOneQueue(q10to19);

	printf("Data	20..29 :");
	printOneQueue(q20to29);

	printf("Data over 29 :");
	printOneQueue(qOver29);

	return;
} // printQueues

/*	printOneQueue
	This function prints the data in one queue,
	ten entries to a line.
		Pre		Queue has been filled
		Post	Data deleted and printed. Queue is empty
*/
void printOneQueue(QUEUE* pQueue) {
	// Local Definitions
	int lineCount;
	int* dataPtr;

	// Statements
	lineCount = 0;
	while (!emptyQueue(pQueue)) {
		dequeue(pQueue, (void*)&dataPtr);
		if (lineCount++ >= 10) {
			lineCount = 1;
			printf("\n	");
		} // if
		printf("%3d	", *dataPtr);
	} // while !emptyQueue

	printf("\n");

	return;
} // printOneQueue