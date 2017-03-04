#include<stdio.h>
#include<stdlib.h>
#include"tree.h"
int main()
{
  int i,n;
  n=3;
  node *tree=NULL;
  elementtype a[MAX];
  for(i=0; i<n; i++)
    {
      printf("Nhap tu: ");gets(a[i].word);
      printf("So lan xuat hien: ");scanf("%d",&a[i].count);getchar();
      tree = insert(tree,a[i]);
    }
  //inorder(tree);
  breath_order(tree);
}
