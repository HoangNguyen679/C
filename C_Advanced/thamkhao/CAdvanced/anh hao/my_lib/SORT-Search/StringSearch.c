/*
* String Search
* In this program, T is a string and P is a pattern string
* Use different algorithm to search P int T and Ouput 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int NaiveSM(char *P, char *T);
void OutputS(int s, int lenP, char *T);
int BoyerMoore(char *P, char *T);
int KMP(char *P, char *T);

int main(int argc, char const *argv[]) {
	char T[100] = "aabbab";
	char P[100]      = "bab";
	if (argc == 3) {
		strcpy(P, argv[1]);
		strcpy(T, argv[2]);
	}
	int lenP = strlen(P);

	//NaiveSM(P, T);
	//BoyerMoore(P, T);
	RabinKarp(P, T);

	return 0;
}

int NaiveSM(char *P, char *T){
	int s, i;
	int lenP = strlen(P);
	int lenT = strlen(T);
	for (s = 0; s <= lenT-lenP; s++){
		i = 0;
		while (i <= lenP && P[i]==T[i+s]){
			i++;
		}
		if (i >= lenP) 
			OutputS(s, lenP, T);
			//return 1; //uncomment if search only one time
	}
}

int BoyerMoore(char *P, char *T){
	int s, i, j;
	int lenP = strlen(P);
	int lenT = strlen(T);
	int last[256];
	
	//Compute last
	for (i = 0; i < 256; i++)
		last[i] = 0;
	for (i = lenP; i >= 0; i--) {
		if (last[P[i]] == 0) {
			last[P[i]] = i;
		}
	}

	//Boyer-moore algorithm
	for (s = 0; s <= lenT-lenP; ){
		j = lenP-1;
		while (j >= 0 && P[j]==T[j+s]) j--;
		if (j == -1) {
			OutputS(s, lenP, T);
			s = s+1;
		} else {
			s += (j-last[T[j+s]]) > 0 ? (j-last[T[j+s]]) : 1;
		}
	}
}

int RabinKarp(char *P, char *T){
	int lenP = strlen(P), lenT = strlen(T);
	int p = 0, t[lenT-lenP+1];
	t[0] = 0;
	int q = 100000; //why this fuck??? cho q =13, 23 -> false??
	int offset = 1;

	int i, j;
	for (i = 0; i < lenP; i++) 
		p = (2*p + P[i]) % q;
	printf("%d", p);
	
	for (i = 0; i < lenP; i++)
		offset = offset*2 % q;

	for (i = 0; i < lenP; i++)
		t[0] = (2*t[0] + T[i]) %q;
	printf("-%d-", t[0]);

	for (i = 1; i <= lenT-lenP; i++) {
		t[i] = (2*t[i-1] - offset*T[i-1] + T[i+lenP-1]) % q; 
		printf("-%d-", t[i]);
	}

	for (i = 0; i <= lenT-lenP; i++) {
		if (t[i] == p) {
			printf("%d", 1);
			for (j = 0; j < lenP; j++) {
				if (P[j] != T[j+i]) break;
			}
			if (j == lenP) {
				OutputS(i, lenP, T);
				printf("2");
			}
		}
	}
}

int KMP(char *P, char *T){}

void OutputS(int s, int lenP, char *T){
	int i;
	for (i = s; i < lenP+s; i++){
		printf("%c", T[i]);
	}
	printf("\n");
}