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
			printf("Distance from vertex %d to vertex %d is: %f\n", i, 
				nodes[i]->first_l->vertex, nodes[i]->first_l->dist);
			if(nodes[i]->first_l->next_lpoint){
				head = nodes[i]-> first_l-> next_lpoint;
			}
			while(head){
				printf("Distance from vertex %d to vertex %d is: %f\n", i, 
					head->vertex, head->dist);

				head = head->next_lpoint;
			}
			head = nodes[i]->first_l;
			while(head){
				lpoint* temp = head;
				head = head->next_lpoint;
				del_lpoint(temp);
			}
			if(nodes[i]){
            	del_node(nodes[i]);
			}
		}
		else{
			if(nodes[i]){
				del_node(nodes[i]);
			}
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

// Another test for generating the adjacency list 
void test_four(int numpoints, int dimension, node* nodes[], time_t t){
	  build_graph(numpoints, dimension, nodes, t);
      printf("Built graph alright\n");
      list_builder(numpoints, dimension, nodes, t);
      printf("Built List alright\n");
      for(int i = 0; i < numpoints; i++){
        lpoint* head = NULL;
        if(nodes[i]->first_l){
          if(nodes[i]->first_l->next_lpoint){
            head = nodes[i]->first_l->next_lpoint;
          }
          printf("Edge from V_%d to V_%d. Dist: %f\n", i, nodes[i]->first_l->vertex, nodes[i]->first_l->dist);
          while(head){
            printf("Edge from V_%d to V_%d. Dist: %f\n", i, head->vertex, head->dist);
            head = head->next_lpoint;
          }
          head = nodes[i]->first_l;
          while(head){
            lpoint* temp = head;
            head = head->next_lpoint;
            del_lpoint(temp);
          }
          del_node(nodes[i]);
          printf("Deleted all the vertexes and the node itself for vertex %d\n", i);
        }
        else{
          del_node(nodes[i]);
        printf("No vertexes in adjacency list for vertex %d\n", i);
        }
      }
      printf("All's well that ends well\n");
}

//generate output to manually ensure that an MST is generated
void test_five(int numpoints, int dimension, node* nodes[], time_t t, int root, float dist[], int prev[]){
	build_graph(numpoints, dimension, nodes, t);
	printf("Built graph alright\n");
	list_builder(numpoints, dimension, nodes, t);
	printf("Built List alright\n");
    for(int i = 0; i < numpoints; i++){
	    lpoint* head = NULL;
	    if(nodes[i]->first_l){
	      if(nodes[i]->first_l->next_lpoint){
	        head = nodes[i]->first_l->next_lpoint;
	      }
	      printf("Edge from V_%d to V_%d. Dist: %f\n", i, nodes[i]->first_l->vertex, nodes[i]->first_l->dist);
	      while(head){
	        printf("Edge from V_%d to V_%d. Dist: %f\n", i, head->vertex, head->dist);
	        head = head->next_lpoint;
	      }
	    }
	    else{
	    printf("No vertexes in adjacency list for vertex %d\n", i);
	    }
  	}
	prim(nodes, numpoints, root, dist, prev);
	for(int i = 0; i < numpoints; i++){
		printf("Edge from %d to %d\n", prev[i], i);
		printf("Distnace of %f\n", dist[i]);
	}
	//now free everything
	for(int i = 0; i < numpoints; i++){
		lpoint* head = NULL;
		if(nodes[i] ->first_l){
			head = nodes[i] -> first_l;
			while(head){
				lpoint* temp = head;
				head = head->next_lpoint;
				del_lpoint(temp);
			}
			del_node(nodes[i]);
		}
		else{
			del_node(nodes[i]);
		}
	}
}

void test_six(time_t t){
	clock_t start, end;
	float sum_avg = 0;
    float sum_instance = 0;
  	for(int numpoints = 128; numpoints <= 131072; numpoints = numpoints << 1){
  		node* nodes[numpoints];
  		float dist[numpoints];
  		int prev[numpoints];
  		for(int dimension = 0; dimension < 5; dimension++){
  			double time;
  			if(dimension == 1){
	  			continue;
	  		}
	  		prune = prune_lookup(numpoints, dimension);
  			sum_avg = 0;
  			for(int i = 0; i < 5; i++){
  				sum_instance = 0;
	  			build_graph(numpoints, dimension, nodes, t);
	  			list_builder(numpoints, dimension, nodes, t);
	  			start = clock();
	  			prim(nodes, numpoints, 0, dist, prev);
	  			end = clock();
	  			time += (double)(end - start) / CLOCKS_PER_SEC;
	  			//free all of the list objects
	  			for(int j = 0; j < numpoints; j++){
		        	lpoint* head = NULL;
		          	if(nodes[j] ->first_l){
		            	head = nodes[j] -> first_l;
		            while(head){
		              	lpoint* temp = head;
		            	head = head->next_lpoint;
		            	del_lpoint(temp);
		            }
		          }
		          del_node(nodes[j]);
		        }
		     	for(int k = 0; k < numpoints; k++){
		    		sum_instance += dist[k];
		    	}
		    	sum_avg += sum_instance;
  			}
  			printf("%f %d %d %d\n", sum_avg/5, numpoints, 5, dimension);
  			
  			printf("Time %f \n", time / 5);
  		}
	}
}

/* Tests random number generator for bias */
void test_seven(void){
	time_t t;
	float sum = 0;
	srand((unsigned) time(&t));
	for(int i = 0; i < 10000; i++){
		sum += rand_range(t, 1);
	}
	printf("Average is: %f", sum/10000);
}

