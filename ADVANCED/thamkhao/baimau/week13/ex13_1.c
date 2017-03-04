#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"lib_sort_int.h"
#include"libTree.h"
#define MAX 500000
int compare(add data1,add data2)
{if(data1>data2) return 1;
  if(data1==data2) return 0;
  if (data1<data2) return -1;
}
void in(int m[],int n)
{
  int i;
  for(i=0;i<n;i++)
    printf("%5d",m[i]);
  printf("\n");
}
void inTree(node *tree)
{
  if(tree!=NULL)
    {inTree(tree->left);
      printf("%5d",tree->data);
      inTree(tree->right);
    }
}
int main()
{
  time_t t1,t2;
  node *tree=NULL;
  add m[MAX],copy[MAX],i;
  srand(time(NULL));
  for(i=0;i<MAX;i++)
    m[i]=rand()%MAX+1;
  for(i=0;i<MAX;i++)
    copy[i]=m[i];
  time(&t1);
  heapSort(copy,MAX-1);
  time(&t2);
  printf("Time to heap sort: %f\n",(float) t2-t1);
  for(i=0;i<MAX;i++)
    copy[i]=m[i];
  time(&t1);
  insertSort(copy,MAX);
  time(&t2);
  printf("Time to insert sort: %f \n",(float) t2-t1);
  for(i=0;i<MAX;i++)
    copy[i]=m[i];
  time(&t1);
  selectSort(copy,MAX);
  time(&t2);
  printf("Time to select sort: %f\n",(float) t2-t1);
  printf("Get char to come next part...\n");
  exit(1);
  printf("===========================\nPart II:The return of the Tree Structure\n");
  for(i=0;i<MAX;i++)
    tree=insert(tree,m[i]);
  inTree(tree);
  printf("\n");
  return 0;
}
