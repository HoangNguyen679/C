#include<stdio.h>
#include<stdlib.h>
#define MAX 1000


typedef struct
{
  int key;
}element;
element list[MAX];
/*
int binsearch(element list[], int searchnum, int n)
{
  int left = 0, right = n-1, middle;
  while(left <= right)
    {
      middle = (left + right)/2;
      switch(COMPARE(list[middle].key,searchnum))
        {
        case -1: left = middle +1 ; break;
        case 0: return middle;
        case 1: right = middle - 1; break;
        }
    }
  return -1;
}
*/
/*
void verify1(element list1[]. element list2[], int n, int m)
{
  int i,j;
  int marked[MAX];

  for(i = 0; i < m; i++)
    marked[i] = -1
    }
*/
void verify2(element list1[], element list2[], int n, int m)
{
  int i,j;
  i=j=0;
  while(i < n && j < m)
    if (list1[i].key < list2[j].key)
      {
        printf("%d is not in list 2\n",list1[i].key);
        i++;
      }
    else if(list1[i].key == list2[j].key)
      {
        printf("%d is both in 2 list\n", list1[i].key);
        i++;j++;
      }
    else
      {
        printf("%d is not in list 1\n",list2[j].key);
        j++;
      }
  for(;i < n; i++)
    printf("%d is not in list 2\n",list1[i].key);
  for(;j < m; j++)
    printf("%d is not in list 1\n",list2[j].key);
}
int main()
{
  element list1[30],list2[40];
  int i;
  for(i = 0; i < 30; i++)
    list1[i].key = 2*i;
  for(i = 0; i < 40; i++)
    list2[i].key = 3*i;
  verify2(list1,list2,30,40);
}
