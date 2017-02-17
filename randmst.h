//Header file for randmst.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
//Used to represent each "point" on the graph
typedef struct node{ 
    float coord[4];
    lpoint* first_l;
} node;

// Used to represent unpruned nodes any graph is adjacent to
typedef struct lpoint{
	node* next_node;
	float dist;
} lpoint;

/* void build_graph(int numpoints, int dimension)
Sets the coordinates for numpoints nodes in a nodes array
 for a given dimension*/
void build_graph(int numpoints, int dimensions, node* nodes[]);

/* float rand_range(float min, float max)
Used to return a random number between 0 and 1*/
float rand_range(float min, float max);

/* void array_initializer(node* nodes[])
Takes the node array and initializes all to NULL*/
void array_initializer(node* nodes[]);

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

/* coid array_initializer(node* nodes[])
sets every entry in node* nodes to be a node*/
void array_initializer(node* nodes[]);

