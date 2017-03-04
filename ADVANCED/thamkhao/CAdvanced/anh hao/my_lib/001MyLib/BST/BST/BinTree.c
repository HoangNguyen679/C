#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int elementType;

void PrintDataTree(elementType e){
  printf("%d ", e);
}

#include "BSTLib.h"

int main(int argc, char const *argv[]) {
  nodeTree *tree1, *tree2;
  InitTree(&tree1); InitTree(&tree2);
  FILE *f = fopen("bst.txt", "r");
  if (f == NULL) {
    perror("ERROR");
    exit(1);
  }

  int n;
  fscanf(f, "%d", &n);
  int i, temp;
  for(i = 1; i <= n ; i++) {
    fscanf(f, "%d", &temp);
    InsertToBTS(&tree1, temp);
  }
  printf("\nPreOrder Traverse: "); PreOrderTraverser(tree1);
  printf("\nInOrder Traverse : "); InOrderTraverser(tree1);
  printf("\nPostOrder Travers: "); PostOrderTraverser(tree1);
  printf("\n");
  printf("Number of Node: %d\n", NumberNode(tree1));
  printf("Height of tree: %d\n", HeightTree(tree1));
  printf("Number of Leaf: %d\n", NumberLeaf(tree1));
  printf("Number of internal node: %d\n", NumberInternalNode(tree1)-1);
  int count = 0; NumberLeftChild(tree1, &count);
  printf("Number of Right Childs: %d\n", count);

  //printf("%d", (SearchTree(tree1, 3)->element));
  //DeleteNode(&tree1, 7);

  printf("\n");

  PrintTree(tree1, HeightTree(tree1));
  //PrettyPrint(tree1," ");

  FreeTree(&tree1);
  PreOrderTraverser(tree1);
  return 0;
}
