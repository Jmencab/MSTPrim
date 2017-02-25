#include "randmst.h"

/*
 *
 * Implementation of Prim's Algorithm in C
 * HUID: 40940510
 *
 * USAGE SUMMARY: 
 *
 */

void prim(node* G[], int size, int root, float dist[], int prev[]) {
	int set[size];
	heap* H = init_heap(size);
	min_heap_insert(H, root, 0);
	for (int i = 0; i < size; i++) {
		dist[i] = 999; // represents infinity
		prev[i] = -1; // represents nil
		set[i] = 0; // represents not in S
	}
	dist[root] = 0;
	int v = heap_extract_min(H);
	while (v != -1){
		set[v] = 1;	
			if(G[v]->first_l){
			lpoint* head = G[v]->first_l;
				while(head){
					int w = head->vertex;
					if(set[w] == 0){
						if(dist[w] > head -> dist){
							dist[w] = head -> dist;
							prev[w] = v; 
							min_heap_insert(H, w, dist[w]);
						}
					}
					head = head->next_lpoint;
				}
			}
		v = heap_extract_min(H);
	}
	destroy_heap(H);
}

