/* Nguyen Duc Hoang - 9A */
// Date Create: 25/03/2015
#include<stdio.h>
main()
{
  char c;
  int count;
  printf("Nhap vao cac ki tu:\N");
  for (count=0; (c=getchar() != '.'); count++)
    {}
  printf("Number of characters is %d\n",count);
}
