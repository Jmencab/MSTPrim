#include "randmst.h"

/*
 *
 * Implementation of Prim's Algorithm in C
 * HUID: 40940510
 *
 * USAGE SUMMARY: 
 *
 */

int* prim(node* G, int size, int root) {
	int dists[size];
	int prev[size];
	int set[size];
	heap* H = init_heap(size);
	min_heap_insert(H, root, 0);
	for (int i = 0; i < size; i++) {
		dist[i] = 999; // represents infinity
		prev[i] = -1; // represents nil
		set[i] = 0; // represents not in S
	}
	dist[root] = 0;
	int v;
	while (v = heap_extract_min(H), v != -1) {
		set[v] = 1;
		for (int i = 0; i < size; i++) {
			// TODO: FOR EACH EDGE IN G[i]
				if (set[w] == 0) {
					if (dist[w] > LENGTHOFEDGE) {
						dist[w] = LENGTHOFEDGE;
						prev[w] = v;
						min_heap_insert(H, w, dist[w]) // TODO: check for overflow (returns -1)
					}
				}
		}
	}
	destroy_heap(H); 
}