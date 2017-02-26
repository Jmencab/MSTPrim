//Header file for randmst.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>
/***********************************************************
***********************************************************/
//Declarations for things in randmst.c

// Used to represent unpruned nodes any graph is adjacent to
typedef struct lpoint{
	struct lpoint* next_lpoint;
	float dist; 
	int vertex; //to what vertex the edge goes to
} lpoint;

//Used to represent each "point" on the graph
typedef struct node{ 
    float coord[4];
    lpoint* first_l;
} node;

//global array for determining pruning values 
extern float prune_val[11][4];

//global variable holding the pruning value
extern float prune;

/* float prune_lookup(int numpoints, int dimension)
returns the pruning threshold for the given number of 
numpoints and dimension you are running*/
float prune_lookup(int numpoints, int dimension);

/* void build_graph(int numpoints, int dimension)
Sets the coordinates for numpoints nodes in a nodes array
 for a given dimension*/
void build_graph(int numpoints, int dimensions, node* nodes[], time_t t);

/*void list_builder(int numpoints, int dimensions, node* nodes[], time_t t)
Generates the andjacency list and edgeweights for the graph */
void list_builder(int numpoints, int dimensions, node* nodes[], time_t t);

//computes euclidean distance and assigns edge weights accordingly
void euclid(int numpoints, int dimensions, node* nodes[]);

/* float rand_range(time_t t)
Used to return a random number between 0 and 1*/
float rand_range(time_t t, float limit);

/* void array_initializer(node* nodes[], int numpoints)
Takes the node array and initializes all entries to be 
pointers to nodes with initialized coordinates*/
void array_initializer(node* nodes[], int numpoints);

/* node* new_node(void)
Initializes nodes and returns pointer to it*/
node* new_node(void);

/* void del_node(node* node_ptr)
Delete node and free memory*/
void del_node(node* node_ptr);

/* void new_lpoint(void)
Initializes adjacency list entries returns pointer to it*/
lpoint* new_lpoint(void);

/* void del_lpoint(lpoint* l_pointer)
Delete and free the given l_pointer*/
void del_lpoint(lpoint* l_pointer);

/**************************************
***************************************/
//Declaration of tests in randmst_tests.c
//test vertex generator (build_graph)
void test_one(int numpoints, int dimension, node* nodes[], time_t t);
//test adjacency list builder(list_builder)
void test_two(int numpoints, int dimension, node* nodes[], time_t t);
//Test heap operations
void test_three(void);
//similar to test two, slightly different output
void test_four(int numpoints, int dimension, node* nodes[], time_t t);
//this test produces text output  we use to manually verify we are getting an MST
void test_five(int numpoints, int dimension, node* nodes[], time_t t, int root, float dist[], int prev[]);
//this test runs every dimension/numpoint combo needed in the writeup
void test_six(time_t t);

/* HEADER FOR HEAP.C */

// represents nodes in heap
typedef struct heapnode {
	int vertex;
	float val;
} heapnode;

// represents heap itself
typedef struct heap {
	heapnode* contents;
	int length;
	int max_length;
} heap;

// parent of i
int parent(int i);

// left child of i
int left(int i);

// right child of i
int right(int i);

// swaps items at locations a and b
void exchange(heap* A, int a, int b);

/* 
 * MIN HEAPIFY
 * Inputs: pointer to heap, heapnode at which to begin heapifying
 * Outputs: none
 *
 * Description: looks at heapnode and its two children, then fixes 
 * the trio such that the smallest is on top is then recursively 
 * called on any displaced children
 */
void min_heapify(heap* A, int i);

/* 
 * INIT HEAP
 * Inputs: size of heap
 * Outputs: pointer to heap structure
 *
 * Description: makes and empty heap of given size
 */
heap* init_heap(int size);

/* 
 * MIN HEAP INSERT
 * Inputs: pointer to heap, vertex to be inserted, value of vertex
 * Outputs: none
 *
 * Description: inserts vertex into heap
 */
int min_heap_insert(heap* A, int vertex, float val);

/* 
 * HEAP EXTRACT MIN
 * Inputs: pointer to heap
 * Outputs: vertex
 *
 * Description: extracts min value object and maintains heap
 * NOTE: returns -1 when heap is empty
 */
int heap_extract_min(heap* A);

/* 
 * DESTROY HEAP
 * Inputs: pointer to heap
 * Outputs: none
 *
 * Description: frees heap
 */
void destroy_heap(heap* A);
/***********************************************************
***********************************************************/
//Declarations for things in prims.c
//runs the algorithm
void prim(node* G[], int size, int root, float dist[], int prev[]);