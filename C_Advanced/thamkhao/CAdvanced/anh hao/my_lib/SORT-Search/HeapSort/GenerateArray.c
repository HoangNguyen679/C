#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define size 10000

int Randomize(int n){
	int key=0, i;
	for(i=0; i<n; i++){
		key = key*10 + rand()%10;
	}
	return key;
}

int main(int argc, char const *argv[]) {
	srand((unsigned)time(NULL));

	int size;
	int *A;
	int n;
	int i;
	FILE *fileOut;
	fileOut = fopen("Array.txt", "w");

	printf("Size of number: ");
	scanf("%d", &n);

	A = (int*)malloc(sizeof(int)*size);
	fprintf(fileOut, "%d\n", size);

	for(i=0; i<size; i++){
		*(A+i) = Randomize(n);
		//printf("%d ", *(A+i));
		fprintf(fileOut, "%d ", *(A+i));
	}

	fclose(fileOut);
	return 0;
}