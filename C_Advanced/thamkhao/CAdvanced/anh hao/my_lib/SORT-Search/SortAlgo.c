#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#define MAXL 20

int GetMenu(void);
void Swap(int *a, int *b);
void Generate(int *A, int n);
void ShowArray(int *A, int n);

void BubbleSort(int *A, int n);
void InsertionSort(int *A, int n);
void SelectionSort(int *A, int n);
void HeapSort(int *A, int n);
void MaxHeapify(int *A, int root, int n);
void QuickSort(int *A, int left, int right);
void MergeSort(int *A, int left, int right);
void Merge(int *A, int left, int right, int middle);


int *Arr;
int temp[10] = {10,7,6,2,1,3,5,8,4,9};

int main(int argc, char const *argv[]){
	srand((unsigned)time(NULL));
	Arr = (int *)malloc(sizeof(int)*MAXL);

	int menu = 0;
	time_t start, end;

	do{
		switch(menu = GetMenu()){
			case 1: Generate(Arr, MAXL); break;
			case 2: start = clock(); InsertionSort(Arr, MAXL); end = clock(); break;
			case 3: start = clock(); SelectionSort(Arr, MAXL); end = clock(); break;
			case 4: start = clock(); BubbleSort(Arr, MAXL);	   end = clock(); break;
			case 5: start = clock(); HeapSort(Arr, MAXL-1);	   end = clock(); break;
			case 6: start = clock(); QuickSort(Arr, 1, MAXL);  end = clock(); break;
			case 7: start = clock(); MergeSort(Arr, 1, MAXL-1);  end = clock(); break;
			default: printf("Invalid option\n"); break;
		}
		
		
		if (menu >= 2 && menu <= 7) {
			ShowArray(Arr, MAXL);
			printf("Time Elapsed: %f\n", (float)(end - start)/CLOCKS_PER_SEC);	
		}
	} while (menu != 0);

	free(Arr);
	return 0;
}

void HeapSort(int *A, int n){
	int i;
	for (i = n/2; i >= 1; i--) 
		MaxHeapify(A, i, n);
	for (i = n; i >= 2; i--){
		Swap(A+1, A+i);
		MaxHeapify(A, 1, i-1);
	}
}

void MaxHeapify(int *A, int root, int n){
	int left = root*2, right = root*2+1;
	int max = root;
	if (left <= n && A[left] > A[root]) max = left;
	if (right <= n && A[right] > A[max]) max = right;
	if (max != root) {
		Swap(A+root, A+max);
		MaxHeapify(A, max, n);
	}
}

void SelectionSort(int *A, int n){
	int i = 1, j = 1;
	int min;

	for (i = 1; i <= n-2; i++){
		min = i;
		for (j = i+1; j < n; j++){
			if (A[min] > A[j]) {
				min = j;
			}
		}
		Swap(A+i, A+min);
	}
}

void InsertionSort(int *A, int n){
	int i, j = 1, k;
	for (i = 2; i < n; i++){
		j = i-1; k = i;
		while (A[k] < A[j] && j >= 1){
			Swap(A+k, A+j);
			j--; k--;
		}
	}
}

void BubbleSort(int *A, int n){
	int i, j;
	for (i = 1; i < n; i++){
		for (j = i+1; j < n; j++){
			if (A[i] > A[j]) {
				Swap(A+i, A+j);
			}
		}
	}
}

void Generate(int *A, int n){
	int i; A[0] = n;
	for(i = 1; i < n; i++)
		A[i] = rand()%10;
}

int GetMenu(void){
	int menuOption = 0;
	do {
		printf("\n\n---SORT MENU---\n");
		printf("1. Generate\n");
		printf("2. Insertion sort\n");
		printf("3. Selection sort\n");
		printf("4. Bubble sort\n");
		printf("5. Heap sort\n");
		printf("6. Quick sort\n");
		printf("7. Merge sort\n");
		printf("0. Exit\n");
		printf("Your Choice: ");
		scanf("%d", &menuOption);
	} while(menuOption < 0 || menuOption > 7);
	return menuOption;
}

void ShowArray(int *A, int n){
	int i;
	printf("\n");
	for (i = 1; i < n; i++){
		printf("%d - ", A[i]);
	}
	printf("\n");
}

void Swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void QuickSort(int *A, int left, int right){
	int pivot, i, j;
	if (left < right) {
		i = left; j = right;
		pivot = A[left];
		do {
			do i++; while (A[i] < pivot);
			do j--; while (A[j] > pivot);
			if (i < j) Swap(A+i, A+j);
		} while (i < j);
		Swap(A+left, A+j);
		QuickSort(A, left, j);
		QuickSort(A, j+1, right);
	}
}


void MergeSort(int *A, int left, int right){
	if (left >= right) return;
	int middle = (left+right)/2;
	MergeSort(A, left, middle);
	MergeSort(A, middle+1, right);
	Merge(A, left, right, middle);
}

void Merge(int *A, int left, int right, int middle){
	int i = left, j = middle+1;
	int k = 0;
	int TA[right];

	for(k = left; k <= right; k++){
		if (i > middle){
			TA[k] = A[j];
			j++;
		} else if (j > right){
			TA[k] = A[i];
			i++;
		} else {
			if (A[i] < A[j]) {
				TA[k] = A[i];
				i++;
			} else {
				TA[k] = A[j];
				j++;
			}
		}
	}

	for (k = left; k <= right; k++){
		A[k] = TA[k];
	}
}