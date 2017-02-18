/*******************************************
*******************************************/
/*Tests for randmst. Run tests on program by
giving second argument corresponding to the 
test you want to run.*/
/*******************************************
*******************************************/
#include "randmst.h"

//Test One: Print out values generated by graph
void test_one(int numpoints, int dimension, node* nodes[], time_t t){
	build_graph(numpoints, dimension, nodes, t);
		for(int i = 0; i < numpoints; i++){
			for(int j = 0; j < dimension; j++){
				if(j == dimension - 1){
					printf("%f)\n", nodes[i] -> coord[j]);
				}
				else if (j == 0){
					printf("(%f, ", nodes[i] -> coord[j]);
				}
				else{
					printf("%f, ", nodes[i] -> coord[j]);
				}
			}
			del_node(nodes[i]);
		}
}

void test_two(int numpoints, int dimension, node* nodes[], time_t t){
	build_graph(numpoints, dimension, nodes, t);
	list_builder(numpoints, dimension, nodes, t);
	for(int i = 0; i < numpoints; i++){
		lpoint* head = NULL;
		if(nodes[i]->first_l){
			head = nodes[i]-> first_l;
			printf("Distance from vertex %d to vertex %d is: %f\n", i, 
				nodes[i]->first_l->vertex, nodes[i]->first_l->dist);
			while(head->next_lpoint){
				lpoint* temp = head;
				head = head->next_lpoint;
				printf("Distance from vertex %d to vertex %d is: %f\n", i, 
					head->vertex, head->dist);
				del_lpoint(temp);
			}
			del_lpoint(nodes[i]->first_l);
            del_node(nodes[i]);
		}
		else{
			del_node(nodes[i]);
		}
	}
}

void test_three(void){
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