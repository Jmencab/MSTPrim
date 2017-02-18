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
} lpoint;

//Used to represent each "point" on the graph
typedef struct node{ 
    float coord[4];
    lpoint* first_l;
} node;

/* void build_graph(int numpoints, int dimension)
Sets the coordinates for numpoints nodes in a nodes array
 for a given dimension*/
void build_graph(int numpoints, int dimensions, node* nodes[], time_t t);

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

void test_one(int numpoints, int dimension, node* nodes[], time_t t);
