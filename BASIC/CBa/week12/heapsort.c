#include<stdio.h>
#include<stdlib.h>

void heapsort(int a[], int n)
{
  int i,j;
  int temp;
  for(i=n/2; i>0; i--) adjust(a,i,n);
  for(i=n-1; i>0; i--)
    {

