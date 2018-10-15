#include <stdio.h>

// Prototype Statements
void towers(int n, char source, char dest, char auxiliary);

int main(void) {
	// Local Definitions
	int numDisks;

	// Statements
	printf("Please enter number of disks: ");
	scanf_s("%d", &numDisks);

	printf("Start Towers of Hanoi. \n\n");

	towers(numDisks, 'A', 'C', 'B');

	printf("\nI Hope you did`t select 64 and ent the world!\n");
	return 0;
} // main


/*	towers
	Move one disk from source to destination through
	the use of recursion.
		Pre		The tower consists of n disks
				Source, destination, & auxiliary towers
		Post	Steps for moves printed
*/
void towers(int n, char source, char dest, char auxiliary) {
	// Local Definitions
	static int step = 0;

	// Statements
	printf("Towers (%d, %c, %c, %c)\n", n, source, dest, auxiliary);

	if (n == 1)
		printf("\t\tStep %3d: Move from %c to %c \n", ++step, source, dest);
	else {
		towers(n - 1, source, auxiliary, dest);
		printf("\t\tStep %3d: Move from %c to %c \n", ++step, source, dest);
		towers(n - 1, auxiliary, dest, source);
	}

	return;
}
