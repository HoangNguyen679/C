#include <stdio.h>
#include <stdlib.h>


int *A;
int n;

void Exchange(int *a, int *b);
void MaxHeapify(int *A, int i, int n);
void BuildMaxHeap(int *A, int n);
void HeapSort(int *A, int n);
void ReadFile(char* filename);


int main(){
	int i;
	char filename[]="Array.txt";
	ReadFile(filename);
	for(i=1; i<=n; i++)	printf("%d ", A[i]);
	HeapSort(A, n);
	
	printf("\n\nAfter Sort:\n\n");
	zfor(i=1; i<=n; i++)	printf("%d ", A[i]);
	printf("\n");
	return 0;
}


/****************FUNCTIONS*****************/
void ReadFile(char* filename){
	FILE *fileIn;
	if((fileIn=fopen(filename, "r")) == NULL){
		perror("ERROR: ");
		exit(1);
	}
	fscanf(fileIn, "%d", &n);
	A = (int*)malloc(sizeof(int)*(n+1));
	int i = 1;
	while(!feof(fileIn)){
		fscanf(fileIn, "%d", A+i);
		i++;
	}
}

void Exchange(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void MaxHeapify(int *A, int i, int n){
	int l = 2*i;
	int r = 2*i+1;
	int largest;

	if (l<=n && A[l]>A[i]) largest = l;
	else largest = i;

	if (r<=n && A[r]>A[largest]) largest = r;

	if (largest != i){
		Exchange(A+i, A+largest);
		MaxHeapify(A, largest, n);
	}
}

void BuildMaxHeap(int *A, int n){
	int i;
	for(i=n/2; i>=1; i--) MaxHeapify(A, i, n);
}


void HeapSort(int *A, int n){
	BuildMaxHeap(A, n);
	int i;
	for(i=n; i>=2; i--) {
		Exchange(A+1, A+i);
		MaxHeapify(A, 1, i-1);
	}
}