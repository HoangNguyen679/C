#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX 20
#define FILENAME "nokia.dat"
#define FILESAVE "NokiaDB.dat"

typedef struct Element_Type{
  char model[MAX];
  float storage;
  float scrSize;
  int price;
} elementType;

void PrintDataTree(elementType e);

#include "BSTLibNokia.h"
#include "QueueLLLib.h"

void WorkWithKey(nodeTree *tree);
void ImportFile(nodeTree **tree1);
int GetMenu(void);
void clear_buffer();
void BreadthFirst(nodeTree *node);

int main(int argc, char const *argv[]) {
  nodeTree *tree1, *tree2;
  InitTree(&tree1); InitTree(&tree2);

  int menu;
  do{
    switch(menu = GetMenu()){
      case 1: ImportFile(&tree1); break;
      case 2: PreOrderTraverser(tree1); break;
      case 3: InOrderTraverser(tree1);  break;
      case 4: PostOrderTraverser(tree1); break;
      case 5: BreadthFirst(tree1); break;
      case 6: 
      printf("Number of Node: %d\n", NumberNode(tree1));
      printf("Height of tree: %d\n", HeightTree(tree1));
      printf("Number of Leaf: %d\n", NumberLeaf(tree1));
      printf("Number of internal node: %d\n", NumberInternalNode(tree1)-1);
      int count = 0; NumberLeftChild(tree1, &count);
      printf("Number of Right Childs: %d\n", count);
      //PrintTree(tree1, HeightTree(tree1));
      printf("\n"); 
      break;
      case 7: clear_buffer(); WorkWithKey(tree1); break;
      default: printf("Invaild Option\n"); break;
    }
  } while (menu != 0);

  /* Free Tree and Exit*/
  FreeTree(&tree1);
  //PreOrderTraverser(tree1); //just check whether tree is free or not :)) 
  return 0;
}


void PrintDataTree(elementType e){
  //printf("%-20s  %-10d  %5d\n", e.name, e.id, e.grade);
  printf("%s\n", e.model);
}

void WorkWithKey(nodeTree *tree){
  elementType key;
  printf("Input key (model): "); gets(key.model);
  nodeTree *Result = SearchTree(tree, key);
  if (Result == NULL) {
    printf("Not Found!");
    return;
  }
  printf("%-8s  %-12g  %-12.1f  %-10d\n", Result->element.model, Result->element.storage, Result->element.scrSize, Result->element.price);
  
  /*Delete Node
  elementType toDelete;
  toDelete.grade = 7;
  DeleteNode(&tree1, toDelete);*/

  /*int numNodeLower = 0;
  printf("Node Lower than key:\n");
  LowerThanKey(tree, key, &numNodeLower);
  printf("\nNumber of Nodes Lower than key: %d\n", numNodeLower);

  int numNodeHigher = 0;
  printf("Node Higher than key:\n");
  HigherThanKey(tree, key, &numNodeHigher);
  printf("\nNumber of Nodes Higher than key: %d\n", numNodeHigher);*/
}

int GetMenu(void){
  int menuOption = 0;
  do {
    printf("\n\n---SORT MENU---\n");
    printf("1. Import File\n");
    printf("2. PreOrder Traverser\n");
    printf("3. InOrder Traverser\n");
    printf("4. PostOrder Traverser\n");
    printf("5. BFS\n");
    printf("6; Tree Information\n");
    printf("7. Search Tree\n");
    printf("0. Exit\n");
    printf("Your Choice: ");
    scanf("%d", &menuOption);
  } while(menuOption < 0 || menuOption > 7);
  return menuOption;
}

void ImportFile(nodeTree **tree1){
  FILE *f = fopen("nokia.dat", "rb");
  if (f == NULL) {
    perror("ERROR");
    exit(1);
  }

  elementType temp;
  int irc;
  while(1){
    irc = fread(&temp, sizeof(elementType), 1, f);
    if (irc == 0) break;
    InsertToBTS(tree1, temp);
  }
  fclose(f);
}

void clear_buffer(){
  int ch;
  while ((ch=getchar()) != '\n' && ch!= EOF);
}

void BreadthFirst(nodeTree *node){
  QueueType queue;
  if (node != NULL){
    EnQueue(node, &queue);
    while (!IsEmptyQueue(&queue)){
      node = DeQueue(&queue);
      PrintDataTree(node->element);
      if (node->left != NULL) EnQueue(node->left, &queue);
      if (node->right != NULL) EnQueue(node->right, &queue);
    }
  }
}
