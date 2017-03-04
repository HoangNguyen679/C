#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXL 30
#define MAX 100

char US[MAX][MAXL];

void Input(char *filename){
	FILE *f = fopen(filename, "r");
	if (f == NULL) {perror("ERROR"); exit(1);}

	int i;
	for(i=1; i<16; i++) strcpy(US[i], "\0");
	char s[MAXL];
	for(i=16; i<=32; i++) {
		fscanf(f, "%s", s);
		strcpy(US[i], s);
	}
}

void Winner(int i){
	if(i != 1){
		int win = rand()%2;
		if (win%2 == 1) strcpy(US[i/2], US[i]);
		else strcpy(US[i/2], US[i-1]);
	}
}

void Round(){
	int i;
	for(i=31; i>1; ){
		Winner(i);
		i-=2;
	}
}

int HeightTree(int i){
	int count = 0;
	while(i != 0){
		i /= 2;
		count++;
	}
	
	//printf("%d-\n" , count);
	return count;
}

// void InorderTraverser(int i){
// 	if(i >= 32) return;
// 	int j;
// 	InorderTraverser(i*2);
// 	for(j=0; j<HeightTree(i/2); j++) printf("           "); printf("%9s\n", US[i]);
// 	InorderTraverser(i*2+1);
// }

void InorderTraverser(int i){
	if(i >= 32) return;
	int j;
	InorderTraverser(i*2);
	for(j=0; j<HeightTree(i/2); j++) printf("           "); printf("|%s", US[i]);
	int k;
	for(k = 0; k < 10 - strlen(US[i]); k++) printf("-"); printf("|\n");
	//for(j=0; j<HeightTree(i/2); j++) printf("           "); printf("%9s\n","|        ");
	InorderTraverser(i*2+1);
}



int main(int argc, char const *argv[]) {
	srand((unsigned)time(NULL));
	Input("USOpen.txt");
	Round();
	int i;

	printf("\n");
	InorderTraverser(1);

	return 0;
}