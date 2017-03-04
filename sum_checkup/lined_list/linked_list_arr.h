#include <stdio.h>
#define MAX 1000
typedef int elementType;
typedef struct {
	elementType elements[MAX];
	int last;
} arrLIST;

void insert(elementType e, int p, arrLIST* L){
	if(L->last >= MAX) return ;
	if(p > L->last + 1 || p < 1) return ;

	int i;
	for(i = L->last; i >= p; i--)
		L->elements[i+1] = L->elements[i];
	L->last++;
	L->elements[p] = e;
}

void delete(int p, arrLIST* L){
	if(p > L->last || p < 1) return ;

	int i;
	L->last --;
	for(i = p; i <= L->last; i++)
		L->elements[i] = L->elements[i+1];
}

int locate(elementType e, arrLIST L){
	int i;
	for(i = 0; i <= L.last; i++)
		if(e == L.elements[i])
			return i;
	return -1;
}

void printLIST(arrLIST L){
	int i;
	for(i = 0; i <= L.last; i++)
		printf("%d\t",L.elements[i]);
	printf("\n");
}
