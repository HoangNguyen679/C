#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tree.h"

int main()
{
  printf("Tao cay\n");
  treetype T;
  makeNullTree(&T);
  strcpy(T->data,"+");
  add_Left(&T,"!");
  add_Left(&T,"a");
  add_Right(&T,"/");
  add_Right(&(T->right),"d");
  add_Left(&(T->left),"-");
  add_Left(&(T->left->left),"b");
  add_Right(&(T->left->right),"c");
  printPreorder(T);
}



