#include<stdio.h>
int main()
{
  int d,m,y,x;
  char ch1,ch2;
  float f;
 printf("Enter a  number: ");
 scanf("%d",&x);
 printf(" Your number is %d \n",x);
 printf("Enter day month and year: ");
 scanf("%2d%2d%4d",&d,&m,&y);
 printf(" Your time is %d %d %d \n",d,m,y);
 printf("Enter day month and year again: ");
 scanf("%d/%d/%d",&d,&m,&y);
 printf(" Your time is %d/%d/%d \n",d,m,y);
 printf("Enter a real  number: ");
 scanf("%f",&f);
 printf(" Your number is %3f \n",f);
 fflush(stdin);
 printf(" Enter 2 chars :");
 scanf("%c %c",&ch1,&ch2);
 printf(" Your chars are %c %c \n",ch1,ch2);
 return 0;
}
