#include<stdio.h>
#define PI 3.1412
int main()
{
  double r;
  printf("Radius = \n");
  scanf("%f",&r);
  printf("Circle's circumference = %f\n",2.0*PI*r);
  printf("Circle area = %f\n",PI*r*r);
  printf("Sphere's area = %f\n",4.0*PI*r*r);
  printf("Sphere's volume = %f\n",4.0/3.0*PI*r*r*r);
  return 0;
}

