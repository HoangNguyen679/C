CC=gcc
CFLAGS= -g
OBJS=adjgraph.o

all: testcase2 testcase3

test: adjgraph.o
	$(CC) $(CFLAGS) test.c OBJS -o test -Iinc -Llib -lfdr

testcase2: adjgraph.o
	$(CC) $(CFLAGS) testcase2.c $(OBJS) -o testcase2 -I./inc -L./lib -lfdr

testcase3: adjgraph.o
	$(CC) $(CFLAGS) testcase3.c $(OBJS) -o testcase3 -I./inc -L./lib -lfdr

adjgraph.o:
	$(CC) $(CFLAGS) -c adjgraph.c -o $(OBJS) -I./inc -L./lib -lfdr

clean:
	rm -rf *.o test testcase2 testcase3