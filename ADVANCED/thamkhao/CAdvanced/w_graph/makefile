CFLAGS = -g    
all: pr topologicalsort map

pr: pr.o lib.a
	gcc $(CFLAGS) -o pr pr.o lib.a

map: map.o lib.a
	gcc $(CFLAGS) -o map map.o lib.a

topologicalsort: topologicalsort.o lib.a
	gcc $(CFLAGS) topologicalsort.o lib.a -o topologicalsort

map.o: map.c
	gcc $(CFLAGS) -c map.c

topologocalsort.o: topologicalsort.c
	gcc $(CFLAGS) -c topologicalsort.c

pr.o: pr.c
	gcc $(CFLAGS) -c pr.c

lib.a: jrb.o jval.o w_graph.o dllist.o
	ar rcs lib.a jrb.o jval.o w_graph.o dllist.o

jrb.o: jrb.c
	gcc $(CFLAGS) -c jrb.c

jval.o: jval.c
	gcc $(CFLAGS) -c jval.c

w_graph.o: w_graph.c
	gcc $(CFLAGS) -c w_graph.c

dllist.o: dllist.c
	gcc $(CFLAGS) -c dllist.c

clean:
	rm -rf *o *a all 
