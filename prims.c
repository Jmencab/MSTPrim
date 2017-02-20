#include "randmst.h"

/*
 *
 * Implementation of Prim's Algorithm in C
 * HUID: 40940510
 *
 * USAGE SUMMARY: 
 *
 */


// TODO: include starting point s?
int* prim(node* G, int V, int s) {
	int dists[V];
	int prev[V];
	// TODO: empty set
	heap* H = init_heap(V);
	min_heap_insert(H, s, 0);
	for (int i = 0; i < V; i++) {
		dist[i] = 2; // represents infinity?
		prev[i] = -1; 
	}
	dist[s] = 0;
	int v;
	while (v = heap_extract_min(H), i != -1) {
		// TODO: add v to set
		// rest of code here
		// min_heap_insert(H, INT_OBJECT, WEIGHT_VALUE); // returns -1 if full
	}
	
	destroy_heap(H); 
}