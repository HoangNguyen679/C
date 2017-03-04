/* Nguyen Duc Hoang - 9A */
// Date Create: 15/3/2015
#include<stdio.h>
int main()
{
  int t;
  printf("enter your age:");
  scanf("%d",&t);
 if (t<18) printf("You're a child\n");
 else if ((t>=18)&&(t<65)) printf("You're an adult\n");
 else printf("You're a senioe cityzen\n");
  return 0;
}
