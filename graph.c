
#include "randmst.h"

/* Want to be able to run ./randmst 0 numpoints numtrials dimension
We ultimately want an adjacency list that gives the distance to another 
node from one node along relevant edges. */
/*****************************************
*****************************************/
/*TODO ONE: Generate an array of numpoints magnitude along 
with the coordinates associated with each one*/

//Use this global array to determine the pruning value
/*prune_val[0] = {0.602,0.438,0.524,0.496}; n = 128
prune_val[1] = {0.370,0.343,0.445,0.422}; n = 256
prune_val[2] = {0.207,0.257,0.367,0.347}; n = 512
prune_val[3] = {0.110,0.187,0.297,0.281}; n = 1024
prune_val[4] = {0.057,0.135,0.239,0.226}; n = 2048
prune_val[5] = {0.029,0.096,0.191,0.181}; n = 4096
prune_val[6] = {0.015,0.068,0.152,0.144}; n = 8192
prune_val[7] = {0.007,0.049,0.121,0.115}; n = 16,384
prune_val[8] = {0.004,0.034,0.096,0.091}; n = 32,768
prune_val[9] = {0.002,0.024,0.077,0.073}; n = 65,536
prune_val[10] = {0.001,0.017,0.061,0.058}; n = 131,072*/ 

float prune_val[11][4] = 
{0.602,0.438,0.524,0.496,
0.370,0.343,0.445,0.422,
0.207,0.257,0.367,0.347,
0.110,0.187,0.297,0.281,
0.057,0.135,0.239,0.226,
0.029,0.096,0.191,0.181,
0.015,0.068,0.152,0.144,
0.007,0.049,0.121,0.115,
0.004,0.034,0.096,0.091,
0.002,0.024,0.077,0.073,
0.001,0.017,0.061,0.058};

//keep pruning value as a global variable
float prune = 100; //set impossibly hight at first

//function that determines the pruning value
float prune_lookup(int numpoints, int dimension){
  int r_index = 0;
  int c_index = 0;
  switch (numpoints){
    case 128:
      r_index = 0;
    break;
    case 256:
      r_index = 1;
    break;
    case 512:
      r_index = 2;
    break;
    case 1024:
      r_index = 3;
    break;
    case 2048:
      r_index = 4;
    break;
    case 4096:
      r_index = 5;
    break;
    case 8192:
      r_index = 6;
    break;
    case 16384:
      r_index = 7;
    break;
    case 32768:
      r_index = 8;
    break;
    case 65536:
      r_index = 9;
    break;
    case 131072:
      r_index = 10;
    break;
  }

  if(dimension == 0)
    c_index = 0;
  else
    c_index = dimension - 1;

  if(numpoints >= 128){
    prune = prune_val[r_index][c_index];
  }
  return prune;
}

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
    //initialize the first_l
    node_ptr->first_l = NULL;
    return node_ptr;
}

void del_node(node* node_ptr){
    // Can safely assume vector is NULL or fully built.
    if(node_ptr){
      free(node_ptr);
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
  l_pointer->vertex = -1;
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

/*TODO TWO: Build adjacency lists by pruning distances greater than 
radius (will add radius argument later to euclid and build_list functions)*/


//computes euclidean distance and assigns edge weights accordingly
void euclid(int numpoints, int dimensions, node* nodes[]){
  switch(dimensions){
    //for all other cases, need to calculate edge weights based on coordinates
    case 2:
      for(int i = 0; i < numpoints; i++){
        float x_1 = nodes[i]-> coord[0];
        float y_1 = nodes[i]-> coord[1];

        for(int j = i + 1; j < numpoints; j++){
          float x_2 = nodes[j]->coord[0];
          float y_2 = nodes[j]->coord[1];
          double x_diff = (double) (x_2 - x_1);
          double y_diff = (double) (y_2 -y_1);
          double x_diff_square = pow(x_diff, 2);
          double y_diff_square = pow(y_diff, 2);
          float distance = (float) sqrt((x_diff_square + y_diff_square));
          //use info to add to adjacency list
            if(distance <= prune){
              lpoint* new_first = new_lpoint();
              assert(new_first);
              new_first->dist = distance;
              new_first->vertex = j;
              if(nodes[i]->first_l){
                new_first->next_lpoint = nodes[i] ->first_l;
              }
              nodes[i]->first_l = new_first;
              //do the mirror image of this
              lpoint* mirror_edge = new_lpoint();
              assert(mirror_edge);
              mirror_edge->dist = distance;
              mirror_edge->vertex = i;
              if(nodes[j]->first_l){
                mirror_edge->next_lpoint = nodes[j] ->first_l;
              }
              nodes[j]->first_l = mirror_edge;
            }
        }
      }
    break;

    case 3: 
      for(int i = 0; i < numpoints; i++){
          float x_1 = nodes[i]-> coord[0];
          float y_1 = nodes[i]-> coord[1];
          float z_1 = nodes[i]-> coord[2];

          for(int j = i + 1; j < numpoints; j++){
            if(j == i){
              continue;
            }
            float x_2 = nodes[j]-> coord[0];
            float y_2 = nodes[j]-> coord[1];
            float z_2 = nodes[j]-> coord[2];
            double x_diff = (double) (x_2 - x_1);
            double y_diff = (double) (y_2 - y_1);
            double z_diff = (double) (z_2 - z_1);
            double x_diff_square = pow(x_diff, 2);
            double y_diff_square = pow(y_diff, 2);
            double z_diff_square = pow(z_diff, 2);
            float distance = 
              (float) sqrt((x_diff_square + y_diff_square + z_diff_square));
            //use info to add to adjacency list
            if(distance <= prune){
              lpoint* new_first = new_lpoint();
              assert(new_first);
              new_first->dist = distance;
              new_first->vertex = j;
              if(nodes[i]->first_l){
                new_first->next_lpoint = nodes[i] ->first_l;
              }
              nodes[i]->first_l = new_first;
              //do the mirror image of this
              lpoint* mirror_edge = new_lpoint();
              assert(mirror_edge);
              mirror_edge->dist = distance;
              mirror_edge->vertex = i;
              if(nodes[j]->first_l){
                mirror_edge->next_lpoint = nodes[j] ->first_l;
              }
              nodes[j]->first_l = mirror_edge;
            }
          }
      }
    
      break;

      case 4: 
      for(int i = 0; i < numpoints; i++){
          float x_1 = nodes[i]-> coord[0];
          float y_1 = nodes[i]-> coord[1];
          float z_1 = nodes[i]-> coord[2];
          float a_1 = nodes[i]-> coord[3];
          //calculate euclidean distances and then 
          //take care of linked list

          for(int j = i + 1; j < numpoints; j++){
            float x_2 = nodes[j]-> coord[0];
            float y_2 = nodes[j]-> coord[1];
            float z_2 = nodes[j]-> coord[2];
            float a_2 = nodes[j]-> coord[3];
            double x_diff = (double) (x_2 - x_1);
            double y_diff = (double) (y_2 - y_1);
            double z_diff = (double) (z_2 - z_1);
            double a_diff = (double) (a_2 - a_1);
            double x_diff_square = pow(x_diff, 2);
            double y_diff_square = pow(y_diff, 2);
            double z_diff_square = pow(z_diff, 2);
            double a_diff_square = pow(a_diff, 2);
            float distance = 
              (float) sqrt((x_diff_square + y_diff_square + 
              z_diff_square + a_diff_square));
            //use info to add to adjacency list
            if(distance <= prune){
              lpoint* new_first = new_lpoint();
              assert(new_first);
              new_first->dist = distance;
              new_first->vertex = j;
              if(nodes[i]->first_l){
                new_first->next_lpoint = nodes[i] ->first_l;
              }
              nodes[i]->first_l = new_first;
              //do the mirror image of this
              lpoint* mirror_edge = new_lpoint();
              assert(mirror_edge);
              mirror_edge->dist = distance;
              mirror_edge->vertex = i;
              if(nodes[j]->first_l){
                mirror_edge->next_lpoint = nodes[j] ->first_l;
              }
              nodes[j]->first_l = mirror_edge;
            }
          }
        }
      break;
  }
}

void list_builder(int numpoints, int dimensions, node* nodes[], time_t t){


  if(dimensions == 0){
    for(int i = 0; i < numpoints; i++){
      for(int j = i + 1; j < numpoints; j++){
        float wedge = rand_range(t, 1);
        if(wedge <= prune){
          lpoint* new_first = new_lpoint();
          assert(new_first);
          new_first->dist = wedge;
          new_first->vertex = j;
          if(nodes[i]->first_l){
            new_first->next_lpoint = nodes[i]->first_l;
          }
          nodes[i]->first_l = new_first;
          lpoint* mirror_edge = new_lpoint();
          assert(new_lpoint);
          mirror_edge->dist = wedge;
          mirror_edge->vertex = i;
          if(nodes[j]->first_l){
           mirror_edge->next_lpoint = nodes[j]->first_l;
          }
          nodes[j]->first_l = mirror_edge;      
        }
      }
    }
  }
  else{
    //build adjacency list with euclidean distances
    euclid(numpoints, dimensions, nodes);
  }
}
