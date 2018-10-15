#pragma once
#include <stdbool.h>


/*	Locate target in an unordered list of size elements.
		Pre		list must contain at least one item
				last is index to last element in lisit
				target contains the data to be located
				locn is address of index in calling functions
		Post	FOUND : matching index stored in locn address
						return true(found)
				NOT FOUND : last stored in locn address
							return false(not found)
*/
bool seqSearch(int list[], int last, int target, int* locn) {
	// Local Definitions
	int looker;

	// Statements
	looker = 0;
	while (looker < last && target != list[looker])
		looker++;

	*locn = looker;
	return (target == list[looker]);
} // seqSearch

/*	Search an ordered list using Binary Search.
		Pre		list must contain at least one element
				last is index to largest element in list
				target is value of element being sought
				locn is address of index in calling function
		Post	FOUND : locn = index to target element
						return true (found)
				NOT FOUND : locn = index below/above target
							return false (not found)
*/
bool binarySearch(int list[], int last, int target, int* locn) {
	// Local Defintions
	int begin;
	int mid;
	int end;

	// Statements
	begin = 0;
	end = last;
	while (begin <= end) {
		mid = (begin + end) / 2;
		if (target > list[mid])
			// look in upper half
			begin = mid + 1;
		else if (target < list[mid])
			// look in lower half
			end = mid - 1;
		else
			// found : force exit
			begin = end + 1;
	} // end while

	*locn = mid;
	return (target == list[mid]);
} // binarySearch