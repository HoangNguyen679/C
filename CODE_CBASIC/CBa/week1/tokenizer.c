#include<stdio.h>
#include<string.h>
#define SIZE 100

void splitSentence(char *s)

  void delSpace(char *s) {
  int i=0;

}



  int main() {
  char sentence[SIZE],trash1[SIZE];
  int i=0,j=0,k=0;

  printf("Nhap vao mot cau: \n");
  gets(sentence);
  strcpy(trash1,sentence);

  while (trash1[i] != '\0') {
    i++;
    if (trash1[i] == ' '){
      for(j=0;j<i;j++) printf("%c",trash1[j]);
      printf("\n");
      while (trash1[i] != '\0') {
	trash1[k]=trash1[i+1];
	k++;i++;
	      }
      trash1[k+1] = '\0';
      i=0;k=0;
    }
  }
}
