#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define ARRSIZE 	37500
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

		if (i >= j) break;

		Exchange(size_of_element, (char*)a+i*size_of_element, (char*)a+j*size_of_element);
	}	
	Exchange(size_of_element, (char*)a+i*size_of_element, (char*)a+pivot*size_of_element);

	QSort2Way(a, size_of_element, l, j, Compare);
	QSort2Way(a, size_of_element, i+1, r, Compare);
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


	int *a = RandomArray(ARRSIZE);

	QSort2Way(a, sizeof(int), 0, ARRSIZE-1, Compare_int);

	NEWLINE
	for (i = 0; i < ARRSIZE; ++i)
	// {
	// 	printf("%d-", a[i]);
	// }
	free(a);





	end = clock();

	NEWLINE
	printf("Run in %f seconds.\n", (float)(end - start)/CLOCKS_PER_SEC);
	
	getch();
	return 0;
}
