#include <stdio.h>

int a[9] = {3,6,7,2,9,15,1,4,8};

swap(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void InsertSort(int a[], int n){
	int k;
	for(k = 2; k <= n; k++){
		int last = a[k];
		int j = k;
		while(j > 1 && a[j-1] >last){
			a[j] = a[j-1];
			j--;
		}
		a[j] = last;
	}
}

void SelectionSort(int a[], int n){
	int k;
	for(k = 0; k < n; k++){
		int min = k;
		int i;
		for(i = k; i < n; i++)
			if(a[min] > a[i])
				min = i;
		swap(&a[k], &a[min]);
	}
}

int main(int argc, char const *argv[])
{
	InsertSort(a, 9);
	//SelectionSort(a, 9);
	int i;
	for(i = 0; i < 9; i++){
		printf("%d ", a[i]);

	}
	printf("\n");
	return 0;
}