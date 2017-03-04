#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20
typedef struct Element_Type{
  int id;
  char name[MAX];
  int grade;
} elementType;

void PrintDataTree(elementType e);

#include "BSTLibGrade.h"

void WorkWithKey(nodeTree *tree);

int main(int argc, char const *argv[]) {
  nodeTree *tree1, *tree2;
  InitTree(&tree1); InitTree(&tree2);
  FILE *f = fopen("grade.dat", "rb");
  if (f == NULL) {
    perror("ERROR");
    exit(1);
  }

  elementType temp;
  int irc;
  while(1){
    irc = fread(&temp, sizeof(elementType), 1, f);
    if (irc == 0) break;
    InsertToBTS(&tree1, temp);
  }
  fclose(f);

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
  printf("\n");

  //PrintTree(tree1, HeightTree(tree1));

  /*Delete Node*/
  //elementType toDelete;
  //toDelete.grade = 7;
  //DeleteNode(&tree1, toDelete);

  
  WorkWithKey(tree1);
  
  /* Free Tree and Exit*/
  FreeTree(&tree1);
  //PreOrderTraverser(tree1); //just check whether tree is free or not :)) 
  return 0;
}


void PrintDataTree(elementType e){
  //printf("%-20s  %-10d  %5d\n", e.name, e.id, e.grade);
  printf("%5d", e.grade);
}

void WorkWithKey(nodeTree *tree){
  elementType key;
  printf("Input key (grade): "); scanf("%d", &key.grade);

  //printf("%d", (SearchTree(tree1, key)->element));
  if (SearchTree(tree, key) == NULL) {
    printf("Not Found!");
    return;
  }

  int numNodeLower = 0;
  printf("Node Lower than key:\n");
  LowerThanKey(tree, key, &numNodeLower);
  printf("\nNumber of Nodes Lower than key: %d\n", numNodeLower);

  int numNodeHigher = 0;
  printf("Node Higher than key:\n");
  HigherThanKey(tree, key, &numNodeHigher);
  printf("\nNumber of Nodes Higher than key: %d\n", numNodeHigher);
}