/* Nguyen Duc Hoang - 9A */
// Date Create:11/3/2015
#include<stdio.h>
int main()
{
  char day[20];
  int   a,b,c,na,nb,nc; 
  const float A=7.00;
  const float B=5.00;
  const float C=3.00;
 printf("Enter the day of the week :");
 gets(day);
 printf("Enter overnight DVD and the number of day rent :");
 scanf("%d%*c%d",&a,&na);
 printf("Enter Three-day  DVD and the number of 'Three-day' :");
 scanf("%d%*c%d",&b,&nb);
 printf("Enter weeky DVD and the number of 'weekly':");
 scanf("%d%*c%d",&c,&nc);
 printf("%s:\n",day);
 printf("Pay for overnight DVD is : $%g x %d x %d = $%g \n",A,a,na,A*a*na);
 printf("Pay for Three-day DVD is : $%g x %d x %d = $%g \n",B,b,nb,B*b*nb);
 printf("Pay for Weekly DVD is : $%g x %d x %d = $%g \n",C,c,nc,C*c*nc);
 printf("Pay for all is : $%g + $%g + $%g  = $%g \n",A*a*na,B*b*nb,C*c*nc,A*a*na+B*b*nb+C*c*nc);
 return 0;
}
