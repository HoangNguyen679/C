/* Nguyen Duc Hoang - 9A */
// Date Create: 15/3/2015
#include<stdio.h>
int main()
{
  int t,pr;
  float re=0.0;
  const int P = 10;
  const int p=7;
  typedef enum {Weekend,Weekday} day; 
  day d;
  printf("enter the day of week:");
  scanf("%d",&d);
  pr=p;
  if (d==) pr=P;
  printf("enter your age:");
  scanf("%d",&t);
 printf("Movie: The Avenger\n");
  if (t<18) 
    {
      re=0.5;
      printf("Class: %s\n","Child");
    }
  else if ((t>=18)&&(t<65))  printf("Class: %s\n","Adult");
  else 
    {
      re=0.3;
      printf("Class: %s\n","Senior Citizen");
    }
 pr=pr-pr*re;
 printf("Date : %s\n",d);
 printf("Price: %g\n",pr);
  return 0;
}
