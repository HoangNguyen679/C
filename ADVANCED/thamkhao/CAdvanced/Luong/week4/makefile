OBJS = jval.o jrb.o test-jval.o
CC = gcc
DEBUG = -g
CFLAGS = -c $(DEBUG)
LFLAGS = $(DEBUG)

all: test-jval

test-jval: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o test-jval

jval.o: jval.c
	$(CC) $(CFLAGS) jval.c
jrb.o: jrb.c
	$(CC) $(CFLAGS) jrb.c
test-jval.o: test-jval.c
	$(CC) $(CFLAGS) test-jval.c

clean:
	rm *.o test-jval
