#include randmst.h

/*
 *
 * Implementation of a binary heap in C
 * HUID: 40940510
 *
 */

/* STRUCTS */

// represents nodes in heap
typedef struct heapnode {
	lpoint** vertex;
	float val;
} heapnode;

// represents heap itself
typedef struct heap {
	heapnode* contents;
	int length;
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
	heapnode* contents = A->contents
	int temp = contents[a]->val;
	contents[a]->val = contents[b]->vals;
	contents[b]->val = temp;
}

/* CORE FUNCTIONS */

/* 
 * INIT HEAP
 * Inputs: max size of heap
 * Outputs: pointer to heap structure
 *
 * Description: makes and empty heap of given size
 */

heap* init_heap(int size) {
	heap* h = malloc(sizeof(heap));
	h->contents = malloc(sizeof(heapnode*) * size);
	h->length = 0;
	return h;
}

/* 
 * MIN HEAPIFY
 * Inputs: pointer to heap, vertex at which to begin heapifying
 * Outputs: none
 *
 * Description:looks at node and its two children, then fixes the trio such that the smallest
 * is on top is then recursively called on any displaced children
 */

void min_heapify(heap* A, int i){

	// grabs left and right children
	int l = left(i);
	int r = right(i);

	// unpacks heap structure
	heapnode* contents = A->contents;
	int length = A->length;

	// compares parent and left child
	if (l <= length) && (contents[l]->val < contents[i]->val) {
		int smallest = l;
	}
	else {
		int smallest = i;
	}

	// compares with right child
	if (r <= length) && (contents[r]->val < contents[smallest]->val) {
		smallest = r;
	}

	// swaps and recurses if necessary
	if (smallest != i) {
		exchange(A, i, smallest);
		min_heapify(A, smallest);
	}
}


/* 
 * MIN HEAP INSERT
 * Inputs: pointer to heap, vertex at which to begin heapifying
 * Outputs: none
 *
 * Description:looks at node and its two children, then fixes the trio such that the smallest
 * is on top is then recursively called on any displaced children
 */

void min_heap_insert() {

}

/* 
 * MIN HEAP INSERT
 * Inputs: pointer to heap, vertex at which to begin heapifying
 * Outputs: none
 *
 * Description:looks at node and its two children, then fixes the trio such that the smallest
 * is on top is then recursively called on any displaced children
 */
 
void heap_extract_min() {

}
