#include "randmst.h"

int main(int argc, char** argv){
  if(argc > 5 || argc < 1)
    EXIT_FAILURE;
  int run_type = atoi(argv[1]);
  int numpoints = atoi(argv[2]);
  int numtrials = atoi(argv[3]);
  int dimension = atoi(argv[4]);
  prune = prune_lookup(numpoints, dimension);
  node* nodes[numpoints];
  time_t t;
  srand((unsigned) time(&t));
  float dist[numpoints];
  int prev[numpoints];
//First test: just seeing if the values given as coordinates worked
  switch(run_type){
    case 0:{
      float sum_avg = 0;
      float sum_instance;
      //repeat for number of trials
      for(int i = 0; i < numtrials; i++){
        sum_instance = 0;
        //building the graph
        build_graph(numpoints, dimension, nodes, t);
        list_builder(numpoints, dimension, nodes, t);
        //Running prims to build MST
        prim(nodes, numpoints, 0, dist, prev);
        //Freeing data
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
        //summing through distance array
        for(int k = 0; k < numpoints; k++){
          sum_instance += dist[k];
        }
        sum_avg += sum_instance;
      }
      //reporting average at end of trials
      float average = sum_avg / numtrials;
      printf("%f %d %d %d\n", average, numpoints, numtrials, dimension);
    }
    break;

    case 1:
      for(int i = 0; i < numtrials; i++){
        printf("numpoints: %d\n", numpoints);
        printf("dimension: %d\n", dimension);
        test_one(numpoints, dimension, nodes, t);
      }
    break;

    case 2:
      for(int i = 0; i < numtrials; i++){
        test_two(numpoints, dimension, nodes, t);
      }
    break;

    case 3:
      for(int i = 0; i < numtrials; i++){
        test_three();
      }
    break;

    case 4:
      for(int i = 0; i < numtrials; i++){
        test_four(numpoints, dimension, nodes, t);
      }
    break;

    case 5:
      for(int i = 0; i < numtrials; i++){
        test_five(numpoints, dimension, nodes, t, 0, dist, prev);
      }
    break;

    case 6:
      test_six(t);
    break;

    case 7:
      test_seven();
    break;

    case 8:
      test_eight(numpoints, dimension, numtrials, nodes, t, 0, dist, prev);
    break;

    case 9:
      test_nine(0,0,1,1);
      test_nine(1.5,1.5, 3.5, 3.5);
      test_nine(1.45, 3.2, 1.8, 3.6);
      test_nine(0.01, .34, .64, .12);
    break;
  }
EXIT_SUCCESS;
}
