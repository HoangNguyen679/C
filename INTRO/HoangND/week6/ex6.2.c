/* Nguyen Duc Hoang - 9A */
// Date Create: 15/3/2015
#include<stdio.h>
int main()
{
  float f;
  printf("Enter degree: ");
  scanf("%f",&f);
  if (f==0.0) printf("east");
  else if (f==90.0) printf("north\n");
  else if (f==180.0) printf("west\n");
  else if (f==270.0) printf("south\n");
  else if ((f>0.0)&&(f<90.0)) printf("north east\n");
  else if ((f>90.0)&&(f<180.0)) printf("north west\n");
  else if ((f>180.0)&&(f<270.0)) printf("south west\n");
  else  printf("south east\n");
  return 0;
}
