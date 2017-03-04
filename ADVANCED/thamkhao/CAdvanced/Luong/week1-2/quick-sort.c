#include<stdio.h>
#include<stdlib.h>
#include<time.h>


#define LENGTH 1000000


void exch(int *a, int p, int q)
{
  int tmp;
  tmp = a[p];
  a[p] = a[q];
  a[q] = tmp;
}

void sort3way(int a[], int l, int r)
{
  if (r <= l) return;

  int i = l - 1, j = r;
  int p = l - 1, q = r;
  int k;

  while(1){
    while(a[++i] < a[r]);
    while(a[r] < a[--j]) if (j == l) break;
    if(i >= j) break;
    exch(a, i, j);
    if(a[i] == a[r]) exch(a, ++p, i);
    if(a[j] == a[r]) exch(a, --q, j);
  }

  exch(a, i, r);
  j = i - 1;
  i = i + 1;
  for(k = l; k <= p; k++) exch(a, k, j--);
  for(k = r-1; k >= q; k--) exch(a, k, i++);
  sort3way(a, l, j);
  sort3way(a, i, r);

}

void sort2way(int a[], int l, int r)
{
  if (r <= l) return;

  int i = l - 1, j = r;
  int p = l - 1, q = r;

  while(1){
    while(a[++i] < a[r]);
    while(a[r] < a[--j]) if (j == l) break;
    if(i >= j) break;
    exch(a, i, j);
  }

  exch(a, i, r);
  j = i - 1;
  i = i + 1;
  sort2way(a, l, j);
  sort2way(a, i, r);

}


int *genArray(int len)
{
  
  int i;
  int *p;

  p = (int*) malloc(sizeof(int)*len);

  //initialize random generation
  srand(time(NULL));

  for(i = 0; i < len; i++) p[i] = rand()%20;

  return p;
}


int main()
{

  int *p1;
  int *p2 = (int *) malloc(sizeof(int)*LENGTH);
  int i;

  //generate array
  p1 = genArray(LENGTH);
  for(i = 0; i < LENGTH; i++) p2[i] = p1[i];

  //sort2way(p1, 0, LENGTH-1);
  //printf("Done\n");
  //for(i = 0; i < 1000; i++) printf("%d ", p1[i]);
  //printf("\n");
  
  sort3way(p2, 0, LENGTH-1);
  printf("Done\n");
  for(i = 0; i < 100000; i++) printf("%d ", p2[i]);
  printf("\n");

}
