#include "avl.h"

int main() {
	avlTree *T = create();
	int i = 0; 
	int r = 0;

	T->value = 12;
	insert( T, 8);
	insert( T, 16);
	insert( T, 4);
	insert( T, 10);
	insert( T, 14);
	insert( T, 2);
	insert( T, 6);
	insert( T, 5);
	T = balanceNode(T);
	traverseDFS( T, height(T)  );
	printf("\n");

	return 0;
}