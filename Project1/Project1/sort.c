#pragma once

/*	selectionSort
	Sorts list [1...last] by selecting smallest element in
	unsorted portion of array and exchanging it with element
	at beginning of the unsorted list.
		Pre		list must contain at least one item
				last contains index to last list element
		Post	list has been sorted smallest to largest
*/
void selectionSort(int list[], int last) {
	// Local Declarations
	int smallest;
	int holdData;

	// Statements
	for (int current = 0; current < last; current++) {
		smallest = current;
		for (int walker = current + 1; walker <= last; walker++) {
			if (list[walker] < list[smallest]) {
				smallest = walker;
			}
		} // for current

		// Smallest selected: exchange with current
		holdData = list[current];
		list[current] = list[smallest];
		list[smallest] = holdData;
	} 
	return;
} // selectionSort

/*	heapSort
	Sort an array, [list0 .. last], using a heap.
		Pre		list must contain at least one item
				last contains index to last element in list
		Post	list has been sorted smallest to largest
*/
void heapSort(int list[], int last) {
	// Local Definitions
	int sorted;
	int holdData;

	// Statements
	// Create Heap
	for (int walker = 1; walker <= last; walker++)
		reheapUp(list, walker);

	// Heap created. Now sort it.
	sorted = last;
	while (sorted > 0) {
		holdData = list[0];
		list[0] = list[sorted];
		list[sorted] = holdData;
		sorted--;
		reheapDown(list, 0, sorted);
	} // while

	return;
} // heapSort

/*	reheapUp
	Reestablishes heap by moving data in child up to
	correct location heap array.
		Pre		heap is array containing an invalid heap
				newNode is index location to new data in heap
		Post	newNode has been inserted into heap
*/
void reheapUp(int* heap, int newNode) {
	// Local Declarations
	int parent;
	int hold;

	// Statements
	// if not at root of heap
	if (newNode) {
		parent = (newNode - 1) / 2;
		if (heap[newNode] > heap[parent]) {
			// child is greater than parent
			hold = heap[parent];
			heap[parent] = heap[newNode];
			heap[newNode] = hold;
			reheapUp(heap, parent);
		} // if heap[]
	} // if newNode
	return;
} // reheapUp

/*	reheapDown
	Reestablishes heap by moving data in root down to its
	correct location in the heap.
		Pre		heap is an array of data
				root is root of heap or subheap
				last is an index to the last element in heap
		Post	heap has been restored
*/
void reheapDown(int* heap, int root, int last) {
	// Local Declarations
	int hold;
	int leftKey;
	int rightKey;
	int largeChildKey;
	int largeChildIndex;

	// Statements
	if ((root * 2 + 1) <= last) {
		// There is at leat one child
		leftKey = heap[root * 2 + 1];
		if ((root * 2 + 2) <= last)
			rightKey = heap[root * 2 + 2];
		else
			rightKey = -1;

		//Determine which child is larger
		if (leftKey > rightKey) {
			largeChildKey = leftKey;
			largeChildIndex = root * 2 + 1;
		}
		else {
			largeChildKey = rightKey;
			largeChildIndex = root * 2 + 2;
		} // else

		// Test if root > larger subtree
		if (heap[root] < heap[largeChildIndex]) {
			// parent < children
			hold = heap[root];
			heap[root] = heap[largeChildIndex];
			heap[largeChildIndex] = hold;
			reheapDown(heap, largeChildIndex, last);
		} // if root <
	} // if root
	return;
} // reheapDown

/*	insertionSort
	Sort using Insertion Sort. The List is divided into
	sorted/unsorted list. In each pass, first element in
	unsorted list is inserted into sorted list.
		Pre		list must contain at least one element
				last contains index to last element in list
		Post	list has been rearranged
*/
void insertionSort(int list[], int last) {
	// Local Definitions
	int hold;
	int walker;

	// Statements
	for (int current = 1; current <= last; current++) {
		hold = list[current];
		for (walker = current - 1; walker >= 0 && hold < list[walker]; walker--)
			list[walker + 1] = list[walker];
		list[walker + 1] = hold;
	} // for current
	return;
} // insertionSort

/*	List[1], list[2], ..., list[last] are sorted in place
	so that the keys are ordered, list[1].key <= list[2].key,
	<= ... <= list[last].key.
		Pre		list is an unordered array of integers
				last is index to last element in array
		Post	list is ordered
*/
void shellSort(int list[], int last) {
	// Local Definitions
	int hold;
	int incre;
	int walker;

	// Statements
	incre = last / 2;
	while (incre != 0) {
		for (int curr = incre; curr <= last; curr++) {
			hold = list[curr];
			walker = curr - incre;
			while (walker >= 0 && hold < list[walker]) {
				// Move larger element up in list
				list[walker + incre] = list[walker];
				// Fall back one partition
				walker = (walker - incre);
			} // while

			// Insert hold in proper position
			list[walker + incre] = hold;
		} // for walk
		// End of pass -- calculate next increment.
		incre = incre / 2;
	} // while
	return;
} // shellSort

/*	bubbleSort
	Sort list using bubble sort. Adjacent elements are
	compared and exchanged until list is ordered.
		Pre		list must contain at least one item
				last contains index to last list element
		Post	list has been sorted in ascending sequence
*/
void bubbleSort(int list[], int last) {
	// Local Definitions
	int temp;

	// Statements
	// Each iteration is one sort pass
	for(int current = 0, sorted = 0; current <= last && !sorted; current++) 
		for(int walker = last, sorted = 1; walker > current; walker--)
			if (list[walker] < list[walker - 1]) {
				// Any exchange means list is not sorted
				sorted = 0;
				temp = list[walker];
				list[walker] = list[walker - 1];
				list[walker - 1] = temp;
			} // if
	return;
} // bubbleSort

/*	quickSort
	Array, sortData[left..right] sorted using recursion.
		Pre		sortData is an array of data to be sorted
				left identifies first element of sortData
				right identifies last element of sortData
		Post	sortData array is sorted
*/
void quickSort(int sortData[], int left, int right) {
	#define MIN_SIZE 16

	// Local Definitions
	int sortLeft;
	int sortRight;
	int pivot;
	int hold;

	// Statements
	if ((right - left) > MIN_SIZE) {
		medianLeft(sortData, left, right);
		pivot = sortData[left];
		sortLeft = left + 1;
		sortRight = right;
		while (sortLeft <= sortRight) {
			// Find key on left that belongs on right
			while (sortData[sortRight] >= pivot)
				sortRight = sortRight - 1;
			if (sortLeft <= sortRight) {
				hold = sortData[sortLeft];
				sortData[sortLeft] = sortData[sortRight];
				sortData[sortRight] = hold;
				sortLeft = sortLeft + 1;
				sortRight = sortRight - 1;
			} // if
		} // while
		// Prepare for next pass
		sortData[left] = sortData[sortLeft - 1];
		sortData[sortLeft - 1] = pivot;
		if (left < sortRight)
			quickSort(sortData, left, sortRight - 1);
		if (sortLeft < right)
			quickSort(sortData, sortLeft, right);
	} // if right
	else
		quickInsertion(sortData, left, right);

	return;
} // quickSort

/*	quickInsertion
	Sort data[1...last] using insertion sort. Data is divided
	into sorted and unsorted lists. With each pass, the first
	element in unsorted list is inserted into the sorted list.
	This is a special version of the insertion sort modified
	for use with quick sort.
		Pre		data must contain at least one element 
				first is index to first element in data
				last is index to last element in data
		Post	data has been rearranged
*/
void quickInsertion(int data[], int first, int last) {
	// Local Definitions
	int hold;
	int walker;

	// Statements
	for (int current = first + 1; current <= last; current++) {
		hold = data[current];
		walker = current - 1;
		while (walker >= first && hold < data[walker]) {
			data[walker + 1] = data[walker];
			walker = walker - 1;
		} // while

		data[walker + 1] = hold;
	} // for

	return;
} // quickInsertion

/*	medianLeft
	Find the median value of an array,
	sortData[left...right], and place it in the
	location sortData[left].
		Pre		sortData is array of at least three elements
				left and right are boundaries of array
		Post	median value placed at sortData[left]
*/
void medianLeft(int sortData[], int left, int right) {
	// Local Definitions
	int mid;
	int hold;

	// Statements
	// Rearrange sortData so median is middle location
	mid = (left + right) / 2;

	if(sortData[left] > sortData[mid]) {
		hold = sortData[left];
		sortData[left] = sortData[mid];
		sortData[mid] = hold;
	} // if
	if (sortData[left] > sortData[right]) {
		hold = sortData[left];
		sortData[left] = sortData[right];
		sortData[right] = hold;
	} // if
	if (sortData[mid] > sortData[right]) {
		hold = sortData[mid];
		sortData[mid] = sortData[right];
		sortData[right] = hold;
	} // if

	// Median is in middle. Exchange with left
	hold = sortData[left];
	sortData[left] = sortData[mid];
	sortData[mid] = hold;

	return;
} // medianLeft