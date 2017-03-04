#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRSIZE 	100
#define RANGE 		100000

void Swap(int *a, int *b)
{
	int temp = *b;
	*b = *a;
	*a = temp;
}

void Partition3Way(int a[], int l, int r)
{
	// check
	if (r <= l) return;
	int i = l - 1; int j = r;
	int p = l - 1; int q = r;

	// Repeat until pointers cross
	while (1)
	{
		// Scan from left >= element
		while (a[++i] < a[r]);
		// Scan from right for <= element
		while (a[--j] > a[r]) if (j == l) break;
		// Check if array is already partitioned
		if (i >= j) break;
		// Exchange 2 elements from left and right
		Swap(&a[i], &a[j]);
		//Move to left or right end if equal
		if (a[i] == a[r]) Swap(&a[i], &a[++p]);
		if (a[j] == a[r]) Swap(&a[j], &a[--q]);
	}
	// Exchange pointer cross to right end element (partition element)
	Swap(&a[i], &a[r]);

	j = i - 1;
	i = i + 1;

	int k;
	// Swap elements on left & right with elements in middle 
	for (k = l; k <= p; k++) Swap(&a[k], &a[j--]);
	for (k = r-1; k >= q; k--) Swap(&a[k], &a[i++]);
	
	// Recursion for left and right
	Partition3Way(a, l, j);
	Partition3Way(a, i, r);	
}

int *RandomArray(int size)
{
	int *a = (int *)malloc(size*sizeof(int));

	int i;
	for (i = 0; i < size; ++i)
	{
		a[i] = rand() % RANGE;
	}

	return a;
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	/* code */
	printf("%s", "3-Ways Partitioned Sort\n");

	int *a = RandomArray(ARRSIZE);

	int i;

	time_t start,end;
	double t;
	start = clock();

	Partition3Way(a, 0, ARRSIZE-1);
	
	end = clock();

	// for (i = 0; i < ARRSIZE; ++i)
	// {
	// 	printf("%d-", a[i]);
	// }

	printf("Run in %f seconds.\n", (float)(end - start)/CLOCKS_PER_SEC);

	free(a);

	return 0;
}
