/* Nguyen Duc Hoang - 9A */
// Date Create: 28/03/2015
#include<stdio.h>
main()
{
  int i,j;
  for(i=0;i<16;i++)
    {
      for(j=0;j<16;j++)
          printf("%d-%c | ",j+i*16,j+i*16);
      printf("\n");
    }
}
