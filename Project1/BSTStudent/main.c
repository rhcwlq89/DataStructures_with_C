/*	This program builds and prints a student list.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "BinarySearchTreeADT.h"

// Structures
typedef struct {
	int id;
	char name[40];
	float gpa;
} STUDENT;

// Prototype Declarations
char getOption(void);
void addStu(BST_TREE* list);
void deleteStu(BST_TREE* list);
void findStu(BST_TREE* list);
void printList(BST_TREE* list);
void testUtilties(BST_TREE* tree);
int compareStu(void* stu1, void* stu2);
void processStu(void* dataPtr);

int main(void) {
	// Local Definitions
	BST_TREE* list;
	char option = ' ';

	// Statements
	printf("Begin Student List\n");
	list = BST_Create(compareStu);

	while ((option = getOption()) != 'Q') {
		switch (option) {
			case 'A': addStu(list);
				break;
			case 'D': deleteStu(list);
				break;
			case 'F': findStu(list);
				break;
			case 'P': printList(list);
				break;
			case 'U': testUtilties(list);
				break;
		} // switch
	} // while

	list = BST_Destroy(list);
	printf("\nEnd Student List\n");
	return 0;
} // main

/*	getOption
	Reads and validates processing option from keyboard.
		Pre		Nothing
		Post	valid option returned
*/
char getOption(void) {
	// Local Definitions
	char option;
	bool error;

	// Statements
	printf("\n ====== MENU ======\n");
	printf("A	Add Student\n");
	printf("D	Delete Student\n");
	printf("F	Find Student\n");
	printf("P	Print Class List\n");
	printf("U	Show Utilities\n");
	printf("Q	Quit\n");

	do {
		printf("\nEnter Option: ");
		scanf_s("%c", &option, sizeof(option));
		option = toupper(option);
		if (option == 'A' || option == 'D' || option == 'F' ||
			option == 'P' || option == 'U' || option == 'Q')
			error = false;
		else {
			printf("Invalid option. Please re-enter: ");
			error = true;
		} 
	} while (error == true);

	return option;
} // getOption

/*	addStu
	Adds a student to tree.
		Pre		nothing.
		Post	student added (abort on memory overflow)
*/
void addStu(BST_TREE* list) {
	// Local Definitions
	STUDENT* stuPtr;

	// Statements
	stuPtr = (STUDENT*)malloc(sizeof(STUDENT));
	if (!stuPtr)
		printf("Memory Overflow in add\n"), exit(100);

	printf("Enter student id:");
	scanf_s("%d", &(stuPtr->id));
	printf("Enter student name:");
	scanf_s("%39s", stuPtr->name, sizeof(stuPtr->name));
	printf("Enter student gpa:");
	scanf_s("%f", &(stuPtr->gpa));

	BST_Insert(list, stuPtr);
} // addStu

/*	deleteStu
	Deletes a student from the tree.
		Pre		nothing
		Post	student deleted or error message printed
*/
void deleteStu(BST_TREE* list) {
	// Local Definitions
	int id;
	int* idPtr = &id;

	// Statements
	printf("Enter student id:");
	scanf_s("%d", idPtr);

	if (!BST_Delete(list, idPtr))
		printf("ERROR: No Student: %0d\n", *idPtr);
} // deleteStu

/*	findStu
	Finds a student and prints name and gpa.
		Pre		student id
		Post	student data printed or error message
*/
void findStu(BST_TREE* list) {
	// Local Definitions
	int id;
	STUDENT* stuPtr;

	// Statements
	printf("Enter student id: ");
	scanf_s("%d", &id);
	stuPtr = (STUDENT*)BST_Retrieve(list, &id);
	if (stuPtr) {
		printf("Student id: %04d\n", id);
		printf("Student name: %s\n", stuPtr->name);
		printf("Student gpa: %4.1f\n", stuPtr->gpa);
	} // if
	else 
		printf("Student %d not in file\n", id);
} // findStu

/*	printList
	Prints a list of students.
		Pre		list has been created (may be null)
		Post	students printed
*/
void printList(BST_TREE* list) {
	// Statements
	printf("\nStudent List:\n");
	BST_Traverse(list, processStu);
	printf("End of Student List\n");
	return;
} // printList

/*	testUtilties
	This function tests the ADT utilities by calling
	each in turn and printing the results.
		Pre		tree has benn created
		Post	results printed
*/
void testUtilties(BST_TREE* tree) {
	// Statements
	printf("Tree contains %3d nodes: \n", BST_Count(tree));
	if (BST_Empty(tree))
		printf("The tree IS empty\n");
	else
		printf("The tree IS NOT empty\n");
	if (BST_Full(tree))
		printf("The tree IS full\a\n");
	else
		printf("The tree IS NOT full\n");
	return;
} // testUtilities

/*	compareStu
	Compare two student id's and return low, equal, high.
		Pre		stu1 and stu2 are valid pointers to students
		Post	return low(-1), equal(0), or high(+1)
*/
int compareStu(void* stu1, void* stu2) {
	// Local Definitions
	STUDENT s1;
	STUDENT s2;

	s1 = *(STUDENT*)stu1;
	s2 = *(STUDENT*)stu2;

	if (s1.id < s2.id)
		return -1;

	if (s1.id == s2.id)
		return 0;

	return +1;
} // compareStu

/*	processStu
	Print one student's data
		Pre		stu is a pointer to a student
		Post	data printed and line advanced
*/
void processStu(void* stuPtr) {
	// Local Definitions
	STUDENT aStu;

	// Statements
	aStu = *(STUDENT*)stuPtr;
	printf("%04d %-40s %4.1f\n", aStu.id, aStu.name, aStu.gpa);

	return;
} // processStu