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
	
  char T[100] = "aabcbacbab";
  char P[100]      = "acbab";
  int lenP = strlen(P);
  int i;

  //NaiveSM(P, T);
  BoyerMoore(P, T);


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
    printf("-%d-", j);
    if (j == -1) {
      OutputS(s, lenP, T);
      s = s+1;
    } else {
      s += (j-last[T[j+s]]) > 0 ? (j-last[T[j+s]]) : 1;
    }
  }
}

int KMP(){}

void OutputS(int s, int lenP, char *T){
  int i;
  for (i = s; i < lenP+s; i++){
    printf("%c", T[i]);
  }
  printf("\n");
}
