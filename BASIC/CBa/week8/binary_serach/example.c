#include<stdio.h>
#include<stdlib.h>
#define max 100

typedef int elementtype;

int binarySearch(elementtype a[],elementtype x,int low, int high)
{
  if(low > high) return -1;
  int mid;
  mid = (low + high)/2;
  if(a[mid] < x)return binarySearch(a,x,mid+1,high);
  else if(a[mid] > x) return binarySearch(a,x,low,mid-1);
  else return mid;
  return -1;
}

int main()
{
  static int A[ ] = { 1, 3, 5, 7, 9, 13, 15 };
  int sizeofA = sizeof( A ) / sizeof( A[ 0 ] );
  int i;
  for( i = 0; i < 20; i++ )
    printf("BinarySearch of %d returns %d\n",i,binarySearch(A,i,0,sizeofA));
  return 0;
}
  
