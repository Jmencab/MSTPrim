#include "randmst.h"

/*
 *
 * Implementation of a binary heap in C
 * HUID: 40940510
 *
 */

/* STRUCTS */

// represents nodes in heap
typedef struct heapnode {
	int vertex;
	float val;
} heapnode;

// represents heap itself
typedef struct heap {
	heapnode* contents;
	int length;
	int max_length;
} heap;

/* HEAP NAVIGATION */

// TODO: Implement these as bitwise operators

// parent of i
int parent(int i) {
	return floor(i/2);
}

// left child of i
int left(int i) {
	return 2 * i;
}

// right child of i
int right(int i) {
	return 2 * i + 1;
}

/* HELPER FUNCTIONS */

// swaps items at locations a and b
void exchange(heap* A, int a, int b) {
	heapnode* contents = A->contents;
	heapnode temp = contents[a];
	contents[a] = contents[b];
	contents[b] = temp;
}

/* 
 * MIN HEAPIFY
 * Inputs: pointer to heap, heapnode at which to begin heapifying
 * Outputs: none
 *
 * Description: looks at heapnode and its two children, then fixes 
 * the trio such that the smallest is on top is then recursively 
 * called on any displaced children
 */

void min_heapify(heap* A, int i){

	// grabs left and right children
	int l = left(i);
	int r = right(i);

	// unpacks heap structure
	heapnode* contents = A->contents;
	int length = A->length;

	// compares parent and left child
	int smallest;
	if (l <= length && contents[l].val < contents[i].val) {
		smallest = l;
	}
	else {
		smallest = i;
	}

	// compares with right child
	if (r <= length && contents[r].val < contents[smallest].val) {
		smallest = r;
	}

	// swaps and recurses if necessary
	if (smallest != i) {
		exchange(A, i, smallest);
		min_heapify(A, smallest);
	}
}

/* USER FUNCTIONS */

/* 
 * INIT HEAP
 * Inputs: size of heap
 * Outputs: pointer to heap structure
 *
 * Description: makes and empty heap of given size
 */

heap* init_heap(int size) {
	heap* h = malloc(sizeof(heap));
	if (h == NULL) {
		return NULL;
	}

	h->contents = malloc(sizeof(heapnode) * (size + 1));
	if (h->contents == NULL) {
		return NULL;
	}

	h->length = 0;
	h->max_length = size;
	return h;
}

/* 
 * MIN HEAP INSERT
 * Inputs: pointer to heap, vertex to be inserted, value of vertex
 * Outputs: none
 *
 * Description: inserts vertex into heap
 */

int min_heap_insert(heap* A, int vertex, float val) {

	// if heap is full
	if (A->length == A->max_length) {
		return -1;
	}

	
	// place new node at bottom
	(A->length)++;
	heapnode* contents = A->contents;
	int length = A->length;
	contents[length].vertex = vertex;
	contents[length].val = val;

	// bubble up
	int tracker = length;
	while (
			tracker > 1 && 
			contents[parent(tracker)].val > contents[tracker].val
			) 
	{
		exchange(A, tracker, parent(tracker));
		tracker = parent(tracker);
	}

	return 0;

}

/* 
 * HEAP EXTRACT MIN
 * Inputs: pointer to heap
 * Outputs: vertex
 *
 * Description: extracts min value object and maintains heap
 * NOTE: returns -1 when heap is empty
 */

int heap_extract_min(heap* A) {

	// empty heap
	if (A->length == 0) {
		return -1;
	}

	// grab min node
	heapnode* contents = A->contents;
	int min = contents[1].vertex;

	// fix heap
	contents[1] = contents[A->length];
	(A->length)--;
	min_heapify(A, 1);

	return min;
}

/* 
 * DESTROY HEAP
 * Inputs: pointer to heap
 * Outputs: none
 *
 * Description: frees heap
 */

void destroy_heap(heap* A) {
	free(A->contents);
	free(A);
}

/* PRELIMINARY TESTING */

int main(void) {

	// test empty heap
	heap* H = init_heap(10);
	assert(heap_extract_min(H) == -1);
	destroy_heap(H);
	printf("successfully did stuff with empty heap\n");

	// test basic functionality
	H = init_heap(10);
	min_heap_insert(H, 1, 2.1);
	min_heap_insert(H, 3, 0);
	min_heap_insert(H, 2, 2.0);
	min_heap_insert(H, 4, -10);
	assert(heap_extract_min(H) == 4);
	assert(heap_extract_min(H) == 3);
	assert(heap_extract_min(H) == 2);
	assert(heap_extract_min(H) == 1);
	assert(heap_extract_min(H) == -1); // test empty heap
	destroy_heap(H);
	printf("successfully sorted some stuff\n");

	// test heap overflow
	H = init_heap(2);
	assert(min_heap_insert(H, 1, 2.1) == 0);
	assert(min_heap_insert(H, 3, 0) == 0);
	assert(min_heap_insert(H, 2, 2.0) == -1);
	assert(heap_extract_min(H) == 3);
	assert(heap_extract_min(H) == 1);
	assert(heap_extract_min(H) == -1);
	destroy_heap(H);
	printf("successfully passed overflow error\n");
}