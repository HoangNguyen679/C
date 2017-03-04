#include<stdio.h>
#include<stdlib.h>
#include "linked_list_sort.h"
main()
{
  node *root,*cur,*prev;
  root = cur = prev = NULL;
  elementtype a[8],b,c;
  int i;
  for(i=0; i<8; i++)
    {
      a[i].key = 2*i+3;
      insert(&root,&cur,&prev,a[i]);
    }
  printList(root);
  printf("\n\n");
  printNode(root);
  printf("\n\n");
  b.key = 2;
  c.key =2;
  insert(&root,&cur,&prev,b);
  printList(root);
  printf("\n\n");
  delete(&root,&cur,&prev,c);
  printList(root);
}
