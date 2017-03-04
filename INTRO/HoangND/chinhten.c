#include<stdio.h>
#include<string.h>
void trimRight(char s[]) {
    int i=0;
	while (s[i] != '\0')  i++;
	while (s[i-1] == ' ') i--;
	s[i] = '\0';
}
void trimLeft(char s[]) {
  int i=0;
  int j=0;
  while (s[i] == ' ') i++;
  while (s[i] != '\0') {
    s[j] = s[i];
    j++;
    i++;
  }
  s[j] ='\0';
}
void trimMiddle(char s[]) {
  int i=0;
  int j=0;
  int k=0;
  while (s[k] != '\0') {
    i=k;
    if  (s[i] == ' ') {
      j=i;
      while (s[i] == ' ') i++;
      while (s[i] != '\0') {
        s[j+1]=s[i];
        j++;
        i++;
      }
      s[j+1]='\0';
    }
    k++;
  }
}
char* chinhten(char s[]) {
	int i=0;
	if(s[0] >=97 && s[0] <= 122) s[0]-=32;
	while (s[i] != '\0'){
		i++;
		if(s[i] == ' ') {
			if(s[i+1] >=97 && s[i+1] <= 122) s[i+1]-=32;
		}
	}
	return s;
}
int ktraten(char s[]) {
  int i=0;
  while (s[i] != '\0') {
    i++;
    if (s[i] == ' ') return 1;
  }
}
main() {
  char ten[30];
  printf("Nhap ten: ");
  gets(ten);
  trimRight(ten);
  trimLeft(ten);
  trimMiddle(ten);
  if (ktraten(ten) == 1) {
    chinhten(ten);
    puts(ten);
    printf("\n");
  }
  else printf("Loi\n");
}
