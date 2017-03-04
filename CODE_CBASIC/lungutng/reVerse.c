/* Nguyen Duc Hoang - 9A */
// Date Create:
#include<stdio.h>
#include<string.h>
void reVerse(char* s)
{
  int dai = strlen(s);
  char *t=NULL;
   t = &s[dai - 1];
  while (t >= &s[0])
    {
      printf("%c",*t);
      t=t-1;
    }
  printf("\n");
}
main()
{
  char *msg ="taerg s'ti,woW";
  reVerse(msg);
}
