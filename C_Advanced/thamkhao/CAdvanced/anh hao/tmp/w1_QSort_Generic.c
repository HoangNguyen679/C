#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define ARRSIZE 	35000
#define RANGE 		10

#define EPSILON 	1E-7

#define NEWLINE 	printf("%s", "\n");


void Exchange(size_t size_of_element, void* const region1, void* const region2)
{
	void *temp = malloc(size_of_element);
	
	memcpy(temp, region1, size_of_element);
	memcpy(region1, region2, size_of_element);
	memcpy(region2, temp, size_of_element);

	free(temp);
}

int Compare_int(void* const a, void* const b)
{
	int m = *(int*)a;
	int n = *(int*)b;
	if(m == n) return 0;
	return m > n ? 1 : -1;
}

int Compare_float(void* const a, void* const b)
{
	float m = *(float*)a;
	float n = *(float*)b;
	if (fabs(m - n) < EPSILON) return 0;
	return m > n ? 1 : -1;
}

int Compare_string(void* const a, void* const b)
{
	char* s1 = (char*)a;
	char* s2 = (char*)b;
	return strcmp(s1, s2);
}

void qsrt(int *a, int l, int r)
{
	if (r <= l) return;	
	int i = l - 1; int j = r;
	int pivot = r;

	while (1)
	{
		while (a[++i] < a[pivot]);
		while (a[--j] >= a[pivot]) if (j <= l) break;

		if (i >= j) break;

		Exchange(4, a+i, a+j);
	}
	Exchange(4, a+i, a+pivot);

	qsrt(a, l, j);
	qsrt(a, i+1, r);
}


void QSort2Way(void *a, int size_of_element, int l, int r, int(*Compare)(void* const a, void* const b))
{
	// check
	if (r <= l) return;

	int i = l - 1; int j = r;
	int pivot = r;

	while (1)
	{
		while (Compare((char*)a+(++i)*size_of_element, (char*)a+pivot*size_of_element) == -1);
		while (Compare((char*)a+(--j)*size_of_element, (char*)a+pivot*size_of_element) != -1) if (j <= l) break;

		if (i >=j) break;

		Exchange(size_of_element, (char*)a+i*size_of_element, (char*)a+pivot*size_of_element);
	}	
	Exchange(size_of_element, (char*)a+i*size_of_element, (char*)a+pivot*size_of_element);

	QSort2Way(a, size_of_element, l, j, Compare);
	QSort2Way(a, size_of_element, i+1, r, Compare);
}

void QSort3Way(void* a, int size_of_element, int l, int r, int(*Compare)(void* const a, void* const b))
{
	// check
	if (r <= l) return;
	
	int i = l - 1; int j = r;
	int p = l - 1; int q = r;

	// Repeat until pointers cross
	while (1)
	{
		// Scan from left >= element
		while (Compare((char*)a+(++i)*size_of_element, (char*)a+r*size_of_element) == -1);
		// Scan from right for <= element
		while (Compare((char*)a+(--j)*size_of_element, (char*)a+r*size_of_element) == 1) if (j == l) break;

		// Check if array is already partitioned
		if (i >= j) break;
		// Exchange 2 elements from left and right
		Exchange(size_of_element, (char*)a+i*size_of_element, (char*)a+j*size_of_element);

		//Move to left or right end if equal
		if (Compare((char*)a+i*size_of_element, (char*)a+r*size_of_element) == 0) Exchange(size_of_element, (char*)a+i*size_of_element, (char*)a+(++p)*size_of_element);
		if (Compare((char*)a+j*size_of_element, (char*)a+r*size_of_element) == 0) Exchange(size_of_element, (char*)a+j*size_of_element, (char*)a+(--q)*size_of_element);
	}

	// Exchange pointer cross to right end element (partition element)
	Exchange(size_of_element, (char*)a+i*size_of_element, (char*)a+r*size_of_element);

	j = i - 1;
	i = i + 1;

	int k;
	// Swap elements on left & right with elements in middle 
	for (k = l; k <= p; k++) Exchange(size_of_element, (char*)a+k*size_of_element, (char*)a+(j--)*size_of_element);
	for (k = r-1; k >= q; k--) Exchange(size_of_element, (char*)a+k*size_of_element, (char*)a+(i++)*size_of_element);
	
	// Recursion for left and right
	QSort3Way(a, size_of_element, l, j, Compare);
	QSort3Way(a, size_of_element, i, r, Compare);	
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
	
	int i;

	time_t start,end;
	double t;
	start = clock();

/*	// Float sort
	float f[6] = {1.3,1.4,1.1,1.5,1.2,1.34};
	for (i = 0; i < 6; ++i)
	{
		printf("%f-", f[i]);
	}

	QSort3Way(f, sizeof(float), 0, 6-1, Compare_float);
	NEWLINE
	
	for (i = 0; i < 6; i++)
	{
		printf("%f-", f[i]);
	}
*/

/*	// Int sort
	int *a = RandomArray(ARRSIZE);

	// for (i = 0; i < ARRSIZE; ++i)
	// {
	// 	printf("%d-", a[i]);
	// }

	QSort3Way(a, sizeof(int), 0, ARRSIZE-1, Compare_int);

	NEWLINE
	// for (i = 0; i < ARRSIZE; ++i)
	// {
	// 	printf("%d-", a[i]);
	// }
	free(a);
*/

/* 	//String sort
	char s[4][100] = {"ab", "am", "aa", "az"};

	for (i = 0; i < 4; i++)
	{
		printf("%s-", s[i]);
	}

	QSort3Way(s, 100, 0, 3, Compare_string);

	NEWLINE
	for (i = 0; i < 4; i++)
	{
		printf("%s-", s[i]);
	}
*/


	int *a = RandomArray(ARRSIZE);

	// for (i = 0; i < ARRSIZE; ++i)
	// {
	// 	printf("%d-", a[i]);
	// }

	QSort2Way(a, sizeof(int), 0, ARRSIZE-1, Compare_int);

	NEWLINE
	// for (i = 0; i < ARRSIZE; ++i)
	// {
	// 	printf("%d-", a[i]);
	// }
	free(a);

	end = clock();

	NEWLINE
	printf("Run in %f seconds.\n", (float)(end - start)/CLOCKS_PER_SEC);
	
	return 0;
}
