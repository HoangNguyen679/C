#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define ARRSIZE 	10
#define RANGE 		26
#define EPSILON 	1E-7
#define MAX_BUFF 	512
#define NEWLINE 	printf("%s", "\n");

#include "jval.h"

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

void QSort3Way(void* a, int size_of_element, int l, int r, int(*Compare)(void*, void*))
{
	// check
	if (r <= l) return;
	
	int i = l - 1; int j = r;
	int p = l - 1; int q = r;

	// Repeat until pointers cross
	while (1)
	{
		// Scan from left >= element
		while (Compare((char*)a+(++i)*size_of_element, (char*)a+r*size_of_element) < 0);
		// Scan from right for <= element
		while (Compare((char*)a+(--j)*size_of_element, (char*)a+r*size_of_element) > 0) if (j == l) break;

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

Jval *RandomINTArray(int size)
{
	// int *a = (int *)malloc(size*sizeof(int));

	// int i;
	// for (i = 0; i < size; ++i)
	// {
	// 	a[i] = rand() % RANGE;
	// }

	// return a;
	Jval *a = (Jval*)malloc(sizeof(Jval)*size);
	int i;
	for (i = 0; i < size; ++i)
	{
		a[i].i = rand() % RANGE;
	}

	return a;
}

Jval *RandomFLOATArray(int size)
{
	Jval *a = (Jval*)malloc(sizeof(Jval)*size);
	int i;
	for (i = 0; i < size; ++i)
	{
		a[i].f = (float)(rand() % RANGE) / (float)(rand() % RANGE + 1);
	}

	return a;
}

Jval *RandomCHARArray(int size)
{
	Jval *a = (Jval*)malloc(sizeof(Jval)*size);
	int i;
	for (i = 0; i < size; ++i)
	{
		a[i].c = (char)(rand() % RANGE + 97);
	}

	return a;
}

int main(int argc, char const *argv[])
{
	//Jval a;
	//a = new_jval_i(12345);
	//printf("%d\n", jval_i(a));	

	srand(time(NULL));
	// Jval *myJval = RandomFLOATArray(ARRSIZE);
	// QSort3Way(myJval, sizeof(Jval), 0, ARRSIZE-1, Compare_float);

	// NEWLINE
	// //int i;
	// for (int i = 0; i < ARRSIZE; ++i)
	// {
	// 	printf("%f-", myJval[i].f);
	// }
	// free(myJval);

	Jval *myJvalString = RandomCHARArray(ARRSIZE);
	QSort3Way(myJvalString, sizeof(Jval), 0, ARRSIZE-1, Compare_string);

	NEWLINE
	int i;
	for (i = 0; i < ARRSIZE; ++i)
	{
		printf("%c-", myJvalString[i].c);
	}
	free(myJvalString);

	return 0;
}