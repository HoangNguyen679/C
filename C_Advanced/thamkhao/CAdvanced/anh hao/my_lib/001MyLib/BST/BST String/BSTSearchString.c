#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50

typedef struct stringsearch_t {
	char info[MAX];
	int count;
} elementType;

void PrintDataTree(elementType e);

#include "BSTLibSearchString.h"

int main(int argc, char const *argv[]) {
	nodeTree *tree1, *tree2;
	InitTree(&tree1); InitTree(&tree2);
	FILE *f = fopen("BTVN.txt", "r");
	if (f == NULL) {
		perror("ERROR");
		exit(1);
	}

	elementType temp;
	char *pch;
	int irc;
	while(!feof(f)){
		irc = fscanf(f, "%s", temp.info);
		if (irc!=1) break;
		printf("%s ", temp.info);
		pch = strtok(temp.info, " ,.|()-?:");
		while(pch != NULL) {
			strcpy(temp.info, pch);
			temp.count = 1;
			InsertToBTS(&tree1, temp);
			pch = strtok(NULL, " ,.|()-?:");
		}
	}


	printf("\n\nPreOrder Traverse: "); PreOrderTraverser(tree1);
	printf("\n\nInOrder Traverse : "); InOrderTraverser(tree1);
	printf("\n\nPostOrder Travers: "); PostOrderTraverser(tree1);
	printf("\n\n");
	printf("Number of Node: %d\n", NumberNode(tree1));
	printf("Height of tree: %d\n", HeightTree(tree1));
	printf("Number of Leaf: %d\n", NumberLeaf(tree1));
	printf("Number of internal node: %d\n", NumberInternalNode(tree1)-1);
	int count = 0; NumberLeftChild(tree1, &count);
	printf("Number of Right Children: %d\n", count);
	PrintTree(tree1, HeightTree(tree1));

	printf("Input a string to Search: ");
	char m_toSearch[MAX];
	scanf("%s", m_toSearch);
	strcpy(temp.info, m_toSearch);
	printf("Time appears: "); printf("%d", (SearchTree(tree1, temp)->element.count));
	//DeleteNode(&tree1, 7);

	printf("\n");


	//PrintTree(tree1, HeightTree(tree1));
	//PrettyPrint(tree1," ");

	FreeTree(&tree1);
	PreOrderTraverser(tree1);
	return 0;
}


void PrintDataTree(elementType e){
	//printf("%s-%d ", e.info, e.count);
	printf("%s ", e.info);
}
