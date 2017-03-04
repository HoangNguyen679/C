#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


#define WORD "word-linux"
#define MAX 20

char myword[500000][MAX];
int N;
void PrintData(void);
int BinarySearch(int Lo, int Hi, char *key);
/*
int BinarySearch(int Lo, int Hi, t_point key){
	if (Lo > Hi) return -1;
	int Mid = (Lo+Hi) / 2;
	if (ComparePoint(Point[Mid], key) == -1) return BinarySearch(Mid+1, Hi, key);
	if (ComparePoint(Point[Mid], key) == 1) return BinarySearch(Lo, Mid-1, key);
	return Mid;
}
*/

int main(int argc, char **argv){
	if (argc > 2) {
		printf("Invailid Argument! (e.g: ./mylook wordtosearch)\n");
		exit(1);
	}

	FILE *fileIn = fopen(WORD, "r");
	if (fileIn == NULL) {
		perror("ERROR");
		exit(1);
	}

	int i=0;
	while (feof(fileIn) == 0){
		//char temp[MAX];
		if (fgets(myword[i], MAX, fileIn) == NULL) break;
		myword[i++][strlen(myword[i])-1] = '\0';
	}
	N = i;

	if(BinarySearch(0,N,"computer") == -1){
		printf("Key not found!\n");
		exit(1);
	}

	printf("%s", myword[BinarySearch(0,N,"computer")]);

	fclose(fileIn);
	return 0;
}

void PrintData(){
	int i = 0;
	while(i != N){
		printf("%s\n", *((myword)+i));
		i++;
	}
}

int BinarySearch(int Lo, int Hi, char *key){
	
	int Mid = (Lo + Hi) / 2;
	if(Mid == Lo) return -1;
	if(strcmp(myword[Mid], key) > 0) BinarySearch(Lo, Mid-1, key);
	else if(strcmp(myword[Mid], key) < 0) BinarySearch(Mid+1, Hi, key);
	else if(strcmp(myword[Mid], key) == 0) return Mid;
}