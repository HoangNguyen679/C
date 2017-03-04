#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 1000000

void SWAP(int *a,int *b)
{
  int temp =*a;
  *a = *b;
  *b = temp;
}

int int_compare(void const* x, void const *y) 
{
	int m, n;
	m = *((int*)x);
	n = *((int*)y);
	if ( m == n ) return 0;
	return m > n ? 1: -1;
}

int string_compare(const void *a, const void *b)
{
	const char **ia = (const char **)a;
	const char **ib = (const char **)b;
	return strcmp(*ia, *ib);
}

void print_cstring_array(char **array, size_t len)
{
	size_t i;
	for(i=0; i<len; i++)
	printf("%s | ", array[i]);
	putchar('\n');
}

void quick_sort(int [], int , int);

void sort(int [], int, int);

int main(int argc, char const *argv[])
{
	srand((unsigned)time(NULL));
	int a[MAX];
	int i,j;
	
//in thu xem sap xep dung chua
	for(i=0; i<10; i++)
		a[i] = rand() % 10;
	for(i=0; i<10; i++)
		printf("%d\t",a[i]);
	printf("\n\n");
	quick_sort(a,0,9);
	for(i=0; i<10; i++)
		printf("%d\t",a[i]);
	printf("\n\n");
// do thoi gian
	clock_t start,finish;
// 2 partition	
	for(i=0; i<MAX; i++)
		a[i] = rand() % 10;
	start = clock();
	quick_sort(a,0,MAX-1);
	finish = clock();
	printf("%f\n",(double)(finish - start)/CLOCKS_PER_SEC);
	printf("\n\n");
// 3 partiotion	
	for(i=0; i<MAX; i++)
		a[i] = rand() % 10;
	start = clock();
	sort(a,0,MAX-1);
	finish = clock();
	printf("%f\n",(double)(finish - start)/CLOCKS_PER_SEC);
	printf("\n\n");
// ham qsort co san
	for(i=0; i<MAX; i++)
		a[i] = rand() % 10;
	start = clock();
	qsort(a,MAX,sizeof(int),int_compare);
	finish = clock();
	printf("%f\n",(double)(finish - start)/CLOCKS_PER_SEC);
	printf("\n\n");
	return 0;
}

void quick_sort(int a[], int l, int r)
{
  int pivot,i,j;///pivot la phan tu chot
  if(l < r)
    {
      i = l;
      j = r + 1;
      pivot = a[l];
      do
        {
          while(a[++i] < pivot);
          while(a[--j] > pivot);
          if(i<j) SWAP(&a[i],&a[j]);
        }
      while(i<j);
      SWAP(&a[l],&a[j]);
      quick_sort(a,l,j-1);
      quick_sort(a,j+1,r);
    }
}


void sort(int a[], int l, int r)
{
	if(r <= l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while (1)
	{
		while(a[++i] < a[r]);
		while(a[r] < a[--j]) if (j==l) break;
		if(i >= j) break;
		SWAP(&a[i],&a[j]);
		if(a[i] == a[r]) SWAP(&a[++p],&a[i]);
		if(a[j] == a[r]) SWAP(&a[--q],&a[j]);		
	}
	SWAP(&a[i],&a[r]);
	j = i - 1;
	i = i + 1;
	int k;
	for (k = l ; k <= p; k++) SWAP(&a[k],&a[j--]);
	for (k = r-1; k >= q; k--) SWAP(&a[k],&a[i++]);
	sort(a, l, j);
	sort(a, i, r);
}

