#include "randmst.h"

/*
 *
 * Implementation of Prim's Algorithm in C
 * HUID: 40940510
 *
 */

/* INPUTS:
 * G: the graph
 * size: size of graph
 * root: index of root of MST
 * dist: distance array
 * prev: prev array
 * 
 * OUTPUTS:
 *  0 : all good
 * -1 : error
 *
 */
void prim(node* G[], int size, int root, float dist[], int prev[]) {
	/* Initialize */
	int set[size]; // set S of vertices in MST
	heap* H = init_heap(size); // init heap
	min_heap_insert(H, root, 0); // place root in heap

	/* For each vertex, initialize */
	for (int i = 0; i < size; i++) {
		dist[i] = 999; // represents infinity
		prev[i] = -1; // represents nil
		set[i] = 0; // represents not in S
	}
	dist[root] = 0;

	// Extract root
	int v = heap_extract_min(H);
	while (v != -1){ // while heap remains
		set[v] = 1;	// add new vertex to set S
		
			/* ensure all vertices have at least one edge */
			assert(G[v]->first_l);

			lpoint* head = G[v]->first_l;

			/* for each edge from vertex */
			while (head) {
				int w = head->vertex;

				/* if edge leads to new vertex */
				if (set[w] == 0) {

					/* insert into heap if new distance smaller */
					if (dist[w] > head->dist) {
						dist[w] = head->dist;
						prev[w] = v; 
						min_heap_insert(H, w, dist[w]);
					}
				}
				head = head->next_lpoint;
			}

		v = heap_extract_min(H);
	}
	destroy_heap(H);
}

