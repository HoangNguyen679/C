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
main() {
	char s[100];
	gets(s);
	printf("%d\n",strlen(s));
	xtrimRight(s);
    trimLeft(s);
    trimMiddle(s);
    puts(s);
	printf("%d\n",strlen(s));
}
