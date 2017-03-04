#include<stdio.h>
#include<stdlib.h>
#include "tree.h"

main()
{
  node *tree=NULL;
  int i,n,a[100];
  n=5;
  printf("Nhap day: \n");
  for(i=0; i<n; i++)
    {
      scanf("%d",&a[i]);
      tree = insert(tree,a[i]);
    }
  printf("%d\n",find_min(tree)->data);
  printf("%d\n",find_max(tree)->data);
}
