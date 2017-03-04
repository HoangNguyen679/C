CC = gcc
LIB_1 = di_w_graph.c
LIB_2 = lib/llib/libfdr.a

all: di_test

di_test: di_test.o
	$(CC) -o di_test di_test.o $(LIB_1) -I. $(LIB_2) -I -libfdr

di_test.o: di_test.c
	$(CC) -c di_test.c

clean: 
	rm -f *.o di_test