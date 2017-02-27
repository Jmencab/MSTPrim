Make randmst: randmst.c graph.c prims.c heap.c randmst_tests.c
	gcc -std=c99 -o randmst randmst.c graph.c prims.c heap.c randmst_tests.c -lm
