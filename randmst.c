#include "randmst.h"
#define RANDMOD 10000

/* Want to be able to run ./randmst 0 numpoints numtrials dimension
We ultimately want an adjacency list that gives the distance to another 
node from one node along relevant edges. */
/*****************************************
*****************************************/
/*TODO ONE: Generate an array of numpoints magnitude along 
with the coordinates associated with each one*/

/*TODO 1.0: Build for dimension = 0 [0,1] weights on edges*/
/*TODO 1.1: Build for dimension = 2, unit square*/
/*TODO 1.2: Build for dimension = 3, unit cube*/
/*TODO 1.3: Build for dimension = 4, unit hypercube*/


float rand_range(time_t t, float limit){
  float divisor = RAND_MAX/(limit+1);
  float retval;
      
  do { 
    retval = rand() / divisor;
  } while (retval > limit);

  return retval;
}


node* new_node(void){
    // Try to allocate nodes
    node *node_ptr = malloc(sizeof(node));
    if(node_ptr == NULL)
        return NULL;

    //initialize coordinates
    node_ptr->coord[0] = 0;
    node_ptr->coord[1] = 0;
    node_ptr->coord[2] = 0;
    node_ptr->coord[3] = 0;
    return node_ptr;
}

void del_node(node* node_ptr){
    // Can safely assume vector is NULL or fully built.
    if(node_ptr){
      free (node_ptr);
    }
}

lpoint* new_lpoint(void){
  //try to allocate lpoint
  lpoint *l_pointer = malloc(sizeof(lpoint));
  if(l_pointer == NULL)
    return NULL;
  //initialize distance
  l_pointer-> dist = 0;
  l_pointer->next_lpoint = NULL;
  return l_pointer;
}

void del_lpoint(lpoint* l_pointer){
  if(l_pointer){
    free(l_pointer);
  }
}

void array_initializer(node* nodes[], int numpoints){
  for(int i = 0; i < numpoints; i++){
    node* point = new_node();
    assert(point != NULL);
    nodes[i] = point;
  }
}

void build_graph(int numpoints, int dimensions, node* nodes[], time_t t){

  array_initializer(nodes, numpoints);

   switch(dimensions){
     case 0:
        for(int i = 0; i < numpoints; i++){

          nodes[i]->coord[0] = rand_range(t, 1);
        }
        break;
  	
     case 2:
        for(int i = 0; i < numpoints; i++){
          nodes[i]->coord[0] = rand_range(t, 1);
          nodes[i]->coord[1] = rand_range(t, 1);
        }
        break;
    
     case 3:
     	  for(int i = 0; i < numpoints; i++){
          nodes[i]->coord[0] = rand_range(t, 1);
          nodes[i]->coord[1] = rand_range(t, 1);
          nodes[i]->coord[2] = rand_range(t, 1);
        }
     	  break;

     	case 4:
     	  for(int i = 0; i < numpoints; i++){
          nodes[i]->coord[0] = rand_range(t, 1);
          nodes[i]->coord[1] = rand_range(t, 1);
          nodes[i]->coord[2] = rand_range(t, 1);
          nodes[i]->coord[3] = rand_range(t, 1);
        }
     	  break;
   }
}

/*TODO TWO: Build adjacency lists by pruning distances greater than radius*/
int main(int argc, char** argv){
  if(argc > 5 || argc < 1)
    EXIT_FAILURE;
  int run_type = atoi(argv[1]);
  int numpoints = atoi(argv[2]);
  int numtrials = atoi(argv[3]);
  int dimension = atoi(argv[4]);
  node* nodes[numpoints];
  time_t t;
  srand((unsigned) time(&t));
//First test: just seeing if the values given as coordinates worked
  switch(run_type){
    case 0:
    printf("Not yet implemented\n");
    break;

    case 1:
        printf("numpoints: %d\n", numpoints);
        printf("dimension: %d\n", dimension);
        test_one(numpoints, dimension, nodes, t);
    break;
  }

EXIT_SUCCESS;
}