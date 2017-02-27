randmst : randmst.o randmst_tests.o heap.o prims.o graph.o

randmst.o : randmst.c randmst.h
	cc -std=c99 -c  -ggdb randmst.c
randmst_tests.o : randmst_tests.c randmst.h 
	cc -std=c99 -c  -ggdb randmst_tests.c
heap.o: heap.c randmst.h
	cc -std=c99 -c -ggdb heap.c
prims.o: prims.c randmst.h
	cc -std=c99 -c -ggdb prims.c
graph.o: graph.c randmst.h
	cc -std=c99 -c -ggdb graph.c

clean :
	rm randmst randmst.o randmst_tests.o heap.o prims.o
