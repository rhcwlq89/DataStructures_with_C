#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "stackADT.h"
#include "queueADT.h"

typedef struct {
	int count;
	struct vertex* first;
	int(*compare) (void* argu1, void* argu2);
} GRAPH;

typedef struct vertex {
	struct vertex* pNextVertex;
	void* dataPtr;
	int inDegree;
	int outDegree;
	short processed;
	struct arc* pArc;
} VERTEX;

typedef struct arc {
	struct vertex* destination;
	struct arc* pNextArc;
} ARC;

// Prototype Declarations
GRAPH* graphCreate(int(*compare)(void* argu1, void* argu2));
GRAPH* graphDestroy(GRAPH* graph);

void graphInsVrtx(GRAPH* graph, void* dataInPtr);
int graphDltVrtx(GRAPH* graph, void* dltKey);
int graphInsArc(GRAPH* graph, void* pFromKey, void* pToKey);
int graphDltArc(GRAPH* graph, void* pFromKey, void* pToKey);

int graphRetrVrtx(GRAPH* graph, void* pKey, void** pDataOut);
int graphFrstArc(GRAPH* graph, void* pKey, void** pDataOut);

void graphDpthFrst(GRAPH* graph, void(*process)(void* dataPtr));
void graphBrdthFrst(GRAPH* graph, void(*process)(void* dataPtr));

bool graphEmpty(GRAPH* graph);
bool graphFull(GRAPH* graph);
int graphCount(GRAPH* graph);

/*	graphInsVrtx
	This function inserts new data into the graph.
		Pre		graph is pointer to valid graph structure
		Post	data inserted or abort if memory O/F
*/
void graphInsVrtx(GRAPH* graph, void* dataInPtr) {
	// Local Definitions
	VERTEX* newPtr;
	VERTEX* locPtr;
	VERTEX* predPtr;

	//Statements
	newPtr = (VERTEX*)malloc(sizeof(VERTEX));
	if (newPtr) {
		newPtr->pNextVertex = NULL;
		newPtr->dataPtr = dataInPtr;
		newPtr->inDegree = 0;
		newPtr->outDegree = 0;
		newPtr->processed = 0;
		newPtr->pArc = NULL;
		(graph->count)++;
	} // if malloc
	else
		printf("Overflow error 100\a\n"), exit(100);

	// Now find insertion point
	locPtr = graph->first;
	if (!locPtr)
		// Empty graph. Insert at beginning
		graph->first = newPtr;
	else {
		predPtr = NULL;
		while (locPtr && (graph->compare(dataInPtr, locPtr->dataPtr) > 0)) {
			predPtr = locPtr;
			locPtr = locPtr->pNextVertex;
		} // while

		if (!predPtr)
			// Insert before first vertex
			graph->first = newPtr;
		else
			predPtr->pNextVertex = newPtr;

		newPtr->pNextVertex = locPtr;
	} // else
	return;
} // graphInsVrtx

/*	graphDltVrtx
	Deletes existing vertex only if its degree is zero.
		Pre		graph is pointer to graph head structure
				dltKey is key of vertex to be deleted
		Post	Vertex deleted if degree zero
				-or- An error code is returned
		Return	Success +1 if successful
						-1 if degree not zero
						-2 if dltKey not found
*/
int graphDltVrtx(GRAPH* graph, void* dltKey) {
	// Local Definitions
	VERTEX* predPtr;
	VERTEX* walkPtr;

	// Statements
	if (!graph->first)
		return -2;

	// Locate vertex to be deleted
	predPtr = NULL;
	walkPtr = graph->first;
	while (walkPtr && (graph->compare(dltKey, walkPtr->dataPtr) > 0)) {
		predPtr = walkPtr;
		walkPtr = walkPtr->pNextVertex;
	} // walkPtr &&

	if (!walkPtr || graph->compare(dltKey, walkPtr->dataPtr) != 0)
		return -2;

	// Found vertex. Test degree
	if ((walkPtr->inDegree > 0) || (walkPtr->outDegree > 0))
		return -1;

	// OK to delete
	if (!predPtr)
		graph->first = walkPtr->pNextVertex;
	else
		predPtr->pNextVertex = walkPtr->pNextVertex;

	--(graph->count);
	free(walkPtr);
	return 1;
} // graphDltVrtx

/*	graphInsArc
	Adds an arc vertex between two vertices.
		Pre		graph is a pointer to a graph
				fromKey is pointer to start vertex key
				toKey is pointer to dest'n vertex key
		Post	Arc added to adjacency list
		Return	success +1 if successful
						-1 if memory overflow
						-2 if fromKey not found
						-3 if toKey not found
*/
int graphInsArc(GRAPH* graph, void* pFromKey, void* pToKey) {
	// Local Definitions
	ARC* newPtr;
	ARC* arcPredPtr;
	ARC* arcWalkPtr;
	VERTEX* vertFromPtr;
	VERTEX* vertToPtr;

	// Statements
	newPtr = (ARC*)malloc(sizeof(ARC));
	if (!newPtr)
		return (-1);

	// Locate source vertex
	vertFromPtr = graph->first;
	while (vertFromPtr && (graph->compare(pFromKey, vertFromPtr->dataPtr) > 0)) {
		vertFromPtr = vertFromPtr->pNextVertex;
	} // while verFromPtr &&

	if (!vertFromPtr || (graph->compare(pFromKey, vertFromPtr->dataPtr) != 0))
		return (-2);

	// Now locate to vertex
	vertToPtr = graph->first;
	while (vertToPtr && graph->compare(pToKey, vertToPtr->dataPtr) > 0) {
		vertToPtr = vertToPtr->pNextVertex;
	} // while vertToPtr &&

	if (!vertToPtr || (graph->compare(pToKey, vertToPtr->dataPtr) != 0))
		return (-3);

	// From and to vertices located. Insert new arc
	++vertFromPtr->outDegree;
	++vertToPtr->inDegree;
	newPtr->destination = vertToPtr;
	if (!vertFromPtr->pArc) {
		// Inserting first arc for this vertex
		vertFromPtr->pArc = newPtr;
		newPtr->pNextArc = NULL;
		return 1;
	} // if new arc

	// Find insertion point in adjacency (arc) list
	arcPredPtr = NULL;
	arcWalkPtr = vertFromPtr->pArc;
	while (arcWalkPtr && graph->compare(pToKey, arcWalkPtr->destination->dataPtr) >= 0) {
		arcPredPtr = arcWalkPtr;
		arcWalkPtr = arcWalkPtr->pNextArc;
	} // arcWalkPtr &&

	if (!arcPredPtr)
		// Insertion before first arc
		vertFromPtr->pArc = newPtr;
	else
		arcPredPtr->pNextArc = newPtr;
	newPtr->pNextArc = arcWalkPtr;
	return 1;
} // graphInsArc

/*	graphDltArc
	Deletes an existing arc.
		Pre		graph is pointer to graph head structure
				fromKey is key of start vertex
				toKey is key of dest'n of delete vertex
		Post	Arc deleted
		Return	Success +1 if successful
						-2 if fromKey not found
						-3 if toKey not found
*/
int graphDltArc(GRAPH* graph, void* fromKey, void* toKey) {
	// Local Definitions
	VERTEX* fromVertexPtr;
	VERTEX* toVertexPtr;
	ARC* preArcPtr;
	ARC* arcWalkPtr;

	// Statements
	if (!graph->first)
		return -2;

	// Locate source vertex
	fromVertexPtr = graph->first;
	while (fromVertexPtr && (graph->compare(fromKey, fromVertexPtr->dataPtr) > 0))
		fromVertexPtr = fromVertexPtr->pNextVertex;

	if (!fromVertexPtr || graph->compare(fromKey, fromVertexPtr->dataPtr) != 0)
		return -2;

	// Locate destination vertex in adjacency list
	if (!fromVertexPtr->pArc)
		return -3;

	preArcPtr = NULL;
	arcWalkPtr = fromVertexPtr->pArc;
	while (arcWalkPtr && (graph->compare(toKey, arcWalkPtr->destination->dataPtr) > 0)) {
		preArcPtr = arcWalkPtr;
		arcWalkPtr = arcWalkPtr->pNextArc;
	} // while arcWalkPtr &&

	if (!arcWalkPtr || (graph->compare(toKey, arcWalkPtr->destination->dataPtr) != 0))
		return -3;
	toVertexPtr = arcWalkPtr->destination;

	// from, toVertex & arcPtr located. Delete arc
	--fromVertexPtr->outDegree;
	--toVertexPtr->inDegree;
	if (!preArcPtr)
		// Deleting first arc
		fromVertexPtr->pArc = arcWalkPtr->pNextArc;
	else
		preArcPtr->pNextArc = arcWalkPtr->pNextArc;
	free(arcWalkPtr);
	return 1;
} // graphDltArc

/*	graphDpthFrst
	Process data in graph in depth-first order.
		Pre		graph is the pointer to graph head
		Post	vertices "processed".

		Processed Flag :	0 = not processed
							1 = pushed into stack
							2 = processed
*/
void graphDpthFrst(GRAPH* graph, void(*process)(void* dataPtr)) {
	// Local Definitions
	bool success;
	VERTEX* walkPtr;
	VERTEX* vertexPtr;
	VERTEX* vertToPtr;
	STACK* stack;
	ARC* arcWalkPtr;

	// Statements
	if (!graph->first)
		return;

	// Set processed flags to not processed
	walkPtr = graph->first;
	while (walkPtr) {
		walkPtr->processed = 0;
		walkPtr = walkPtr->pNextVertex;
	} // while

	// Process each vertex in list
	stack = createStack();
	walkPtr = graph->first;
	while (walkPtr) {
		if (walkPtr->processed < 2) {
			if (walkPtr->processed < 1) {
				// Push & set flag to pushed
				success = pushStack(stack, walkPtr);
				if (!success)
					printf("\aStack overflow 100\a\n"), exit(100);

				walkPtr->processed = 1;
			} // if processed < 1
		} // if processed < 2
		// Process descendents of vertex at stack top

		while (!emptyStack(stack)) {
			vertexPtr = popStack(stack);
			process(vertexPtr->dataPtr);
			vertexPtr->processed = 2;

			// Push all vertices from adjacency list
			arcWalkPtr = vertexPtr->pArc;
			while (arcWalkPtr) {
				vertToPtr = arcWalkPtr->destination;
				if (vertToPtr->processed == 0) {
					success = pushStack(stack, vertToPtr);
					if (!success)
						printf("\aStack overflow 101\a\n"), exit(101);
					vertToPtr->processed = 1;
				} // if vertToPtr
				arcWalkPtr = arcWalkPtr->pNextArc;
			} // while pWalkArc
		} // while !emptyStack
		walkPtr = walkPtr->pNextVertex;
	} // while walkPtr
	destroyStack(stack);
	return;
} // graphDpthFrst

/*	graphBrdthFrst
	Process the data of the graph in breadth-first order.
		Pre		graph is pointer to graph head structure
		Post	graph has been processed
		Process Flag :	0 = not processed
						1 = enqueued
						2 = processed
*/
void graphBrdthFrst(GRAPH* graph, void(*process) (void* dataPtr)) {
	// Local Definitions
	bool success;
	VERTEX* walkPtr;
	VERTEX* vertexPtr;
	VERTEX* vertToPtr;
	QUEUE* queue;
	ARC* arcWalkPtr;

	// Statements
	if (!graph->first)
		return;

	// Set processed flags to not processed
	walkPtr = graph->first;
	while (walkPtr) {
		walkPtr->processed = 0;
		walkPtr = walkPtr->pNextVertex;
	} // while

	// Process each vertex in list
	queue = createQueue();
	walkPtr = graph->first;
	while (walkPtr) {
		if (walkPtr->processed < 2) {
			if (walkPtr->processed < 1) {
				//Enqueue & set flag to queue
				success = enqueue(queue, walkPtr);
				if (!success)
					printf("\aQueue overflow 100 \a\n"), exit(100);
				walkPtr->processed = 1;
			} // if processed < 1
		} // if processed < 2

		// Process descendents of vertex at que front
		while (!emptyQueue(queue)) {
			dequeue(queue, (void**)&vertexPtr);
			process(vertexPtr->dataPtr);
			vertexPtr->processed = 2;

			// Enqueue vertices from adjacency list
			arcWalkPtr = vertexPtr->pArc;
			while (arcWalkPtr) {
				vertToPtr = arcWalkPtr->destination;
				if (vertToPtr->processed == 0) {
					success = enqueue(queue, vertToPtr);
					if (!success)
						printf("\a Queue overflow 101\a\n"), exit(101);
					vertToPtr->processed = 1;
				} // if vertToPtr
				arcWalkPtr = arcWalkPtr->pNextArc;
			} // while pWalkArc
		} // while !emptyQueue
		walkPtr = walkPtr->pNextVertex;
	} // while walkPtr;
	destroyQueue(queue);
	return;
} // graphBrdthFrst