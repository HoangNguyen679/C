CC = gcc
LIB_1 = di_w_graph.c
LIB_2 = ../lib/llib/libfdr.a
FILE = mocktest2

all: $(FILE)

$(FILE): $(FILE).o
	$(CC) -o $(FILE) $(FILE).o $(LIB_1) -I. $(LIB_2) -I -libfdr

$(FILE).o: $(FILE).c
	$(CC) -c $(FILE).c

clean:
	rm -f *.o $(FILE) 