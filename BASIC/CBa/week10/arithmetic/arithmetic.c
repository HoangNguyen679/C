/*
  write the program using tree to representing the expression: !a + (b-c)/d
*/
#include<stdio.h>
#include<stdlib.h>
#include "tree.h"

main()
{

  node *root = NULL;
  char a,b,c,d;
  printf("Nhap gia tri bieu thuc: \n");
  printf("a = ");scanf("%c",&a);while(getchar() != '\n');
  printf("b = ");scanf("%c",&b);while(getchar() != '\n');
  printf("b = ");scanf("%c",&c);while(getchar() != '\n');
  printf("b = ");scanf("%c",&d);while(getchar() != '\n');
  root =  merge('+',merge('!',creat(a),NULL),merge('/',merge('-',creat(b),creat(c)),creat(d)));
  printf("Mo ta bieu thuc: \n");
  printf("Tien to: \n");preorder(root);printf("\n");
  printf("Hau to: \n");postorder(root);printf("\n");
  printf("Trung to: \n");inorder(root);printf("\n");

  }
