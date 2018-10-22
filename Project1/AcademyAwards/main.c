/*	This program maintains and displays a list of
	Academy Awards Motion Pictures
*/
#include <stdio.h>
#include <stdlib.h>
#include <cType.h>
#include <stdbool.h>
#include "ListADT.h"

#define STR_MAX 41

typedef struct {
	short year;
	char picture[STR_MAX];
	char director[STR_MAX];
} PICTURE;

// Prototype Declarations
void printInstr(void);
LIST* buildList(void);
void process(LIST* list);
char getChoice(void);
void printList(LIST* list);
void search(LIST* list);

int cmpYear(void* pYear1, void* pYear2);

int main(void) {
	// Local Definitions
	LIST* list;
	char aa[STR_MAX];

	scanf_s("%*c", aa);
	printf("%*c", aa);

	// Statements
	printInstr();
	list = buildList();
	process(list);

	printf("End Best Pictures\n"
		"Hope you found your favorite!\n");
	return 0;
} // main

/*	printInstr
	Print instructions to user.
		Pre		Nothing
		Post	instructions printed
*/
void printInstr(void) {
	// Statements
	printf("This program prints the Academy Awards \n"
		"Best Picture of the Year and its director.\n"
		"Your job is to enter the year; we will do\n"
		"the rest. Enjoy.\n");
	return;
} // printInstr

/*	buildList
	Reads a text data file and loads the list
		Pre		file exists in format: yy \t 'pic' \t 'dir'
		Post	list contains data 
				-or- program aborted if problem
*/
LIST* buildList(void) {
	// Local Definitions
	FILE* fpData;
	LIST* list;

	short yearIn;
	int addResult;

	PICTURE* pPic;

	// Statements
	list = createList(cmpYear);
	if (!list)
		printf("\aCannot create list\n"), exit(100);
	fopen_s(&fpData, "pictures.dat", "r");
	if (!fpData)
		printf("\aError opening input file\n"), exit(110);

	while (fscanf_s(fpData, " %hd", &yearIn) == 1) {
		pPic = (PICTURE*)malloc(sizeof(PICTURE));
		if (!(pPic))
			printf("\aOut of Memory in build list\n"), exit(100);
		pPic->year = yearIn;

		// Skip tabs and quote
		while ((fgetc(fpData)) != '\t');
		while ((fgetc(fpData)) != '"');
		fscanf_s(fpData, " %40[^\"], %*c", pPic->picture);
		while ((fgetc(fpData)) != '\t');
		while ((fgetc(fpData)) != '"');
		fscanf_s(fpData, " %40[^\"], %*c", pPic->director);

		// Insert into list
		addResult = addNode(list, pPic);
		if (addResult != 0)
			if (addResult == -1)
				printf("Memory overflow adding movie\a\n"), exit(120);
			else
				printf("Duplicate year %hd not added\n\a", pPic->year);

		while (fgetc(fpData) != '\n');
	} // while
	return list;
} // buildList

/*	process
	Process user choices
		Pre		list has been created
		Post	all of user's choice executed
*/
void process(LIST* list) {
	// Local Definitions
	char choice;

	// Statements
	do {
		choice = getChoice();
		switch (choice) {
			case 'P':printList(list);
				break;
			case 'S':search(list);
			case 'Q': break;
		} // switch
	} while (choice != 'Q');

	return;
} // process

/*	getChoice
	Prints the menu of choices.
		Pre		Nothing
		Post	menu printed and choice returned
*/
char getChoice(void) {
	// Local Definitions
	char choice;
	bool valid;

	// Statements
	printf("======== MENU ======== \n"
		"Here are your choices:\n"
		"	S: Search for a year\n"
		"	P: Print all years\n"
		"	Q: Quit\n\n"
		"Enter your choice: ");

	do {
		scanf_s("%c", &choice);
		choice = toupper(choice);
		switch (choice) {
		case 'S':
		case 'P':
		case 'Q': valid = true;
			break;
		default: valid = false;
			printf("\aInvalid choice\n"
				"Please try again: ");
			break;
		} // switch
	} while (!valid);

	return choice;
} // getChoice

/*	printList
	Prints the entire list
		Pre		list has been created
		Post	list printed
*/
void printList(LIST* list) {
	// Local Definitions
	PICTURE* pPic;

	// Statements
	// Get first node
	if (listCount(list) == 0)
		printf("Sorry, nothing in list\n\a");
	else {
		printf("\nBest Pictures List\n");
		traverse(list, 0, (void**)&pPic);
		do {
			printf("%hd %-40s %s\n", pPic->year, pPic->picture, pPic->director);
		} while (traverse(list, 1, (void**)&pPic));
	} // else

	printf("End of Best Pictures List\n\n");
} // printList

/*	search
	Searches for year and prints year, picture, and
	director.
		Pre		list has been created
				user has selected search option
		Post	year printed or error message
*/
void search(LIST* list) {
	// Local Definitions
	short year;
	bool found;

	PICTURE pSrchArgu;
	PICTURE* pPic;

	// Statements
	printf("Enter a four digit year: ");
	scanf_s("%hd", &year);
	pSrchArgu.year = year;

	found = searchList(list, &pSrchArgu, (void**)&pPic);

	if (found)
		printf("%hd %-40s %s\n", pPic->year, pPic->picture, pPic->director);
	else
		printf("Sorry, but %d is not available.\n", year);

	return;
} // search

/*	cmpYear
	compares two years in PICTURE structures
		Pre		year1 is a pointer to the first structure
				year2 is a pointer to the second structure
		Post	two years compared and result returned
		Return	-1 if year1 less; 0 if equal; +1 greater
*/
int cmpYear(void* pYear1, void* pYear2) {
	// Local Definitions
	int result;
	short year1;
	short year2;

	// Statements
	year1 = ((PICTURE*)pYear1)->year;
	year2 = ((PICTURE*)pYear2)->year;

	if (year1 < year2)
		result = -1;
	else if (year1 > year2)
		result = +1;
	else
		result = 0;

	return result;
} // cmpYear