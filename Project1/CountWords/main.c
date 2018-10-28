/*	This program counts the words in a file.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AVLTreeADT.h"

// Structures
typedef struct {
	char word[51]; // One Word
	int count;
} DATA;

// Prototype Declarations
void buildList(AVL_TREE* wordList);
void insertWord(AVL_TREE* words);
void deleteWord(AVL_TREE* words);
void printList(AVL_TREE* wordList);
void printWord(void* aWord);
bool getWord(DATA* aWord, FILE* fpWords);
int compareWords(void* arguPtr, void* listPtr);

int main(void) {
	// Local Definitions
	AVL_TREE* wordList;

	// Statements
	printf("Start count words in document\n");
	wordList = AVL_Create(compareWords);

	buildList(wordList);
	printList(wordList);

	printf("End count words\n");
	return 0;
} // main

/*	buildList
	Reads file and creates AVL tree containing list
	of all words used in the file with count of the
	number of times each word is found in the file.
		Pre		wordList has been created.
		Post	AVL tree(list) built or error returned
*/
void buildList(AVL_TREE* wordList) {
	// Local Definitions
	char fileName[25];
	FILE* fpWords;

	bool success;
	DATA* aWord;
	DATA newWord;

	// Statements
	printf("Enter name of file to be processed: ");
	scanf_s("%24s", fileName, sizeof(fileName));

	fopen_s(&fpWords, fileName, "r");
	if (!fpWords) {
		printf("%-s could not be opened\a\n", fileName);
		printf("Please verify name and try again.\n");
		exit(100);
	} // !fpWords

	while (getWord(&newWord, fpWords)) {
		aWord = AVL_Retrieve(wordList, &(newWord));
		if (aWord)
			(aWord->count)++;
		else {
			aWord = (DATA*)malloc(sizeof(DATA));
			if (!aWord) {
				printf("Error 120 in buildList\n");
				exit(120);
			} // if

			// Add word to list
			*aWord = newWord;
			aWord->count = 1;
			success = AVL_Insert(wordList, aWord);
			if (!success) {
				printf("Error 121 in buildList\a\n");
				exit(12);
			} // if  overflow test
		} // else
	} // while

	printf("End AVL Tree\n");
	return;
} // buildList

/*	getWord
	Reads one words from file.
		Pre		nothing
		Post	word read into reference parameter
*/
bool getWord(DATA* aWord, FILE* fpWords) {
	// Local Definitions
	char strIn[51];
	int ioResult;
	int lastChar;

	// Statements
	ioResult = fscanf_s(fpWords, "%50s", strIn, sizeof(strIn));
	if (ioResult != 1)
		return false;

	// Copy and remove punctuation at end of word.
	strcpy_s(aWord->word, sizeof(aWord->word), strIn);
	lastChar = strlen(aWord->word) - 1;
	if (ispunct(aWord->word[lastChar]))
		aWord->word[lastChar] = '\0';
	return true;
} // getWord

/*	compareWords
	This function compares two integers identified
	by pointers to integers.
		Pre		arguPtr and listPtr are pointers to DATA
		Return	-1	:	arguPtr value	<	listPtr value
				 0	:	arguPtr value	==	listPtr value
				+1	:	arguPtr value	>	listPtr value
*/
int compareWords(void* arguPtr, void* listPtr) {
	// Local Declarations
	DATA arguValue;
	DATA listValue;

	// Statements
	arguValue = *(DATA*)arguPtr;
	listValue = *(DATA*)listPtr;

	return (strcmp(arguValue.word, listValue.word));
} // compare

/*	printList
	Prints the list with the count for each word.
		Pre		list has been built
		Post	list printed
*/
void printList(AVL_TREE* wordList) {
	// Statements
	printf("\nWords found in list\n");
	AVL_Traverse(wordList, printWord);
	printf("\nEnd of word list\n");
	return;
} // printList

/*	printWord
	Prints one word from the list with its count.
		Pre		ADT calls function to print data
		Post	data printed
*/
void printWord(void* aWord) {
	// Statements
	printf("%-25s %3d\n", ((DATA*)aWord)->word, ((DATA*)aWord)->count);
	return;
} // printWord