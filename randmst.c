#include randmst.h
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

float rand_range(float min, float max){
  time_t t;
  srand((unsigned) time(&t));
  return min + (float) (rand() / (float) (RAND_MAX + 1) * (max - min + 1));
}


node* new_node(void){
    // Try to allocate nodes
    node *node_ptr = malloc(sizeof(node));
    if(retval == NULL)
        return NULL;

    // Try to allocate lpoint in nodes
    node_ptr->lpoint = malloc(sizeof(lpoint));
    if(node_ptr->lpoint == NULL) {
        free(node_ptr);
        return NULL;
    }
    //initialize coordinates
    node_ptr->coord = {0,0,0,0};
    return node_ptr;
}

void del_node(node* node_ptr){
    // Can safely assume vector is NULL or fully built.
    if(node_ptr){
      free(node_ptr->lpoint);
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
  return l_pointer;
}

void del_lpoint(lpoint* l_pointer){
  if(l_pointer){
    free(l_pointer);
  }
}

void array_initializer(node* nodes[]){
  for(i = 0; i < numpoints - 1; i++){
    node* point = new_node;
    assert(point);
    nodes[i] = point;
  }
}

void build_graph(int numpoints, int dimensions, node* nodes[]){

   switch(dimensions){

     case 0:
        for(int i = 0; i < numpoints - 1; i++){

          nodes[i]->coord[0] = rand_range(0,1);
        }
        break;
  	
     case 2:
        for(int i = 0; i < numpoints - 1; i++){
          nodes[i]->coord[0] = rand_range(0,1);
          nodes[i]->coord[1] = rand_range(0,1);
        }
        break;
    
     case 3:
     	  for(int i = 0; i < numpoints - 1; i++){
          nodes[i]->coord[0] = rand_range(0,1);
          nodes[i]->coord[1] = rand_range(0,1);
          nodes[i]->coord[2] = rand_range(0,1);
        }
     	  break;

     	case 4:
     	  for(int i = 0; i < numpoints - 1; i++){
          nodes[i]->coord[0] = rand_range(0,1);
          nodes[i]->coord[1] = rand_range(0,1);
          nodes[i]->coord[2] = rand_range(0,1);
          nodes[i]->coord[3] = rand_range(0,1);
        }
     	  break;

     default : 
     statement(s);
   }
}

/*TODO TWO: Build adjacency lists by pruning distances greater than radius*/