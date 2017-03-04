#include <stdio.h>
#include <string.h>
#define FILENAME "USOpen.txt"
#define MAX_LENGTH 15
#define MAX 1000
typedef char elementType[MAX_LENGTH];
void assignmentElementType(elementType *des, elementType sou){
	strcpy(*des,sou);
}
#include "treelib.h"
#define NULL_STRING ""
FILE *f;
char name[MAX_LENGTH];
typeTree tree;
int is_null_string(elementType a){
	return strcmp(a,NULL_STRING);
}
void printData(int t){
	int i = 5, k = t;
	while (k > 0){
		k = k >> 1;
		i--;
	}
	for (;i > 0;i--) printf("%15s",NULL_STRING);
	printf("%-15s\n",tree.info[t]);
}

int main(int argc, char **argv){
	f = fopen(FILENAME,"r");
	int i = 0;
	for (i=1;i<16;i++) addTree(&tree,NULL_STRING);
	while (1){
		if ( fgets(name,MAX_LENGTH,f) == 0) break;
		addTree(&tree,name);	
	}
	getvalue(&tree,1,&is_null_string);
	inOrderTraverse(&tree,1,&printData);
}