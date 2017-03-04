#include<stdio.h>
main()
{
  int i=0,j=0,th,n;
  char s[100],p[100];
  scanf("%d",&n);
  th=n;
  while (th>0){
    s[i]=th%16;
    th=th/16;
    i++;
  }
  printf("Hexa is: ");
  for (j=i;j>=0;j--)
  {
    if (s[j]<10) printf ("%d",s[j]);
    else
  switch (s[j]) {
    case 10:printf("A");break;
    case 11:printf("B");break;
    case 12:printf("C");break;
    case 13:printf("D");break;
    case 14:printf("E");break;
    case 15:printf("F");break;
      }
  }
  printf("\n");
}