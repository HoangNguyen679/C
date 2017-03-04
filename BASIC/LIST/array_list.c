#include<stdio.h>
#include<stdlib.h>
#define maxlength 1000

typedef int element_type;
typedef struct LIST {
	element_type elements [maxlength];
	int last;
} list_type;


int isEmpty(list_type lp){
	return lp.last == 0;
}

int isFull(list_type lp){
	return lp.last == maxlength;
}


void insert(element_type x, int p, list_type *lp){
	if(lp->last == maxlength) { printf("Full list\n"); return; }
	if(p < 1 || p > lp->last +1) { printf("Wrong location\n"); return; }
	int i=0;
	for(i =  lp->last - 1; i >= p - 1 ; i--){
		lp->elements[i+1] = lp->elements[i];

	}
	lp->elements[p-1] = x;
}

void insertLast(element_type x, list_type *lp){
	lp->last ++;
	lp->elements[lp->last -1] = x;
}

void printList(list_type lp){
	int i;
	for(i = 0; i < lp.last; i++) printf("%d\n",lp.elements[i]);
}

main() {
	list_type lp;
	lp.last = 0;

	int i=0,n=5;
	for(i = 0; i < 5; i++) insertLast(i,&lp) ;
	printList(lp);
	insert(10,3,&lp);
	printList(lp);
}

