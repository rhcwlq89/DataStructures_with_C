#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*	The telephone lookip program using hashing.
	The input is a file of names and phone numbers.
*/

// Global Declarations
typedef struct {
	char name[31];
	char phone[16];
} LISTING;

const int cMax_Size = 53;

// Prototype Declarations
void buildList(LISTING phoneList[], int* last);
void hashSearch(LISTING phoneList[], int last);
int hashKey(char* key, int last);
int collision(int last, int locn);

int main(void) {
	// Local Definitions
	LISTING phoneList[cMax_Size];
	int last;

	// Statements
	printf("Begin Phone Listing\n");

	last = cMax_Size - 1;
	buildList(phoneList, &last);
	hashSearch(phoneList, last);

	printf("\nEnd Phone Listing\n");
	return 0;
}

/*	buildList
	Read phone number file and load into array
		Pre		phoneList is array to be filled
				last is index to last element loaded
		Post	array filled
*/
void buildList(LISTING phoneList[], int* last) {
	// Local Definitions
	FILE* fpPhoneNums;
	LISTING aListing;
	int locn;
	int cntCol;
	int end;

	// Statements
	fpPhoneNums = fopen("P13-03.TXT", "r");
	if (!fpPhoneNums) {
		printf("Can't open phone file\a\n");
		exit(100);
	} // if

	// Set keys to null
	for (int i = 0; i <= *last; i++)
		phoneList[i].name[0] = '\0';

	while (!feof(fpPhoneNums)) {
		fscanf(fpPhoneNums, " %30[^;]%*c %[^;]%*c", aListing.name, aListing.phone);
		locn = hashKey(aListing.name, *last);

		if (phoneList[locn].name[0] != '\0') {
			// Collision
			end = *last;
			cntCol = 0;
			while (phoneList[locn].name[0] != '\0' && cntCol++ <= *last)
				locn = collision(*last, locn);
			
			if (phoneList[locn].name[0] != '\0') {
				printf("List full. Not all read.\n");
				return;
			} // if full list
		} // if collision

		phoneList[locn] = aListing;
	} // while
	return;
} // buildList

/*	hashKey
	Given eky, hash key to location in list.
		Pre		phoneList is hash array
				last is last index in list
				key is string to be hashed
		Post	returns hash location
*/
int hashKey(char* key, int last) {
	// Local Definitions
	int addr;
	int keyLen;

	// Statements
	keyLen = strlen(key);
	addr = 0;

	for (int i = 0; i < keyLen; i++)
		if (key[i] != ' ')
			addr += key[i];

	return (addr% last + 1);
} // hashKey

/*	collision
	Have a collision. Resolve
		Pre		phoneList is hashed list
				last is index of last element in list
				locn is address of collision
		Post	returns next addres in list
*/
int collision(int last, int locn) {
	// Statements
	return locn < last ? ++locn : 0;
} // collision

/*	hashSearch
	Prompt user for name and lookup in array.
		Pre		phoneList has been initialized
		Post	User requested quit
*/
void hashSearch(LISTING* phoneList, int last) {
	// Local Definitions
	char srchName[31];
	char more;
	int locn;
	int maxSrch;
	int cntCol;

	// Statements
	do {
		printf("Enter name: ");
		scanf("%s", srchName);

		locn = hashKey(srchName, last);
		if (strcmp(srchName, phoneList[locn].name) != 0) {
			// treat as collision
			maxSrch = last;
			cntCol = 0;
			while (strcmp(srchName, phoneList[locn].name) != 0 && cntCol++ <= maxSrch)
				locn = collision(last, locn);
		} // if

		// Test for success
		if (strcmp(srchName, phoneList[locn].name) == 0)
			printf("%-32s (%02d) #-15s\n", phoneList[locn].name, locn, phoneList->phone);
		else
			printf("%s not found\n", srchName);

		printf("\nLook up another number <Y/N>? ");
		scanf(" %c", &more);
	} while (more == 'Y' || more == 'y');
} // hashSearch