randmst : randmst.o randmst_tests.o 

randmst.o : randmst.c randmst.h
	cc -c -ggdb randmst.c
randmst_tests.o : randmst_tests.c randmst.h 
	cc -c -ggdb randmst_tests.c

clean :
	rm randmst randmst.o randmst_tests.o 
