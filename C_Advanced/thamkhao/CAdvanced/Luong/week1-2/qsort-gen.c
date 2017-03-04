#include<stdio.h>
#include<stdlib.h>
#include<time.h>


#define LENGTH 1000000


void exch(void *base, int p, int q, size_t size)
{
  int i;
  char *base2 = (char *) base;

  for(i=0;i<size;i++){ 
    char tmp=base2[size*p+i];
    base2[size*p+i]=base2[size*q+i];
    base2[size*q+i]=tmp; 
  }
}

int cmp(const void *a, const void *b)
{
  return *(int *)a - *(int *)b;
}

void sort3way(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *))
{
  int r = nmemb/size-1; /* offset of the last element from base */
  int l = 0;
  if (nmemb <= size) return;

  char *base2 = (char *) base;
  int i = l - 1, j = r;
  int p = l - 1, q = r;
  int k;

  while(1){
    /* look for one that is greater than the last one */
    while((*cmp)(&base2[++i*size], &base2[r*size]) < 0);
    /* look for one that is smaller than the last one */
    while((*cmp)(&base2[r*size], &base2[--j*size]) < 0) if (j == l) break;
    if(i >= j) break; /* no pair found */
    /* exchange element i and j */
    exch(base2, i, j, size);
    /* if element i is equal the last element, exchange it to the begining of the array */
    if(cmp(&base2[i*size], &base2[r*size]) == 0) exch(base2, ++p, i, size);
    /* if element j is equal the last element, exchange it  to the r-1 th position */
    if(cmp(&base2[j*size], &base2[r*size]) == 0) exch(base2, --q, j, size);
  }

  /* put r-th element to the right position */
  exch(base2, i, r, size);
  j = i - 1;
  i = i + 1;
  /* move the elements that are equal to pivot to the middle */
  for(k = l; k <= p; k++) exch(base2, k, j--, size);
  for(k = r-1; k >= q; k--) exch(base2, k, i++, size);
  /* recursively call function */
  sort3way(base2, (j+1)*size, size, cmp);
  /* move base2 to i+1-th positon */
  sort3way(&base2[(i)*size], (r-i+1)*size, size, cmp);

}


int *genArray(int len)
{
  
  int i;
  int *p;

  p = (int*) malloc(sizeof(int)*len);

  //initialize random generation
  srand(time(NULL));

  for(i = 0; i < len; i++) p[i] = rand()%256;

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
  
  sort3way(p1, LENGTH*sizeof(int), sizeof(int), cmp);
  printf("Done\n");
  for(i = 0; i < 1000000; i++) printf("%d ", p1[i]);
  printf("\n");

}
