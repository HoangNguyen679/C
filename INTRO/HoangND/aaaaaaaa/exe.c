#include<stdio.h>
#define MONTHS 12
/*store and display rainfall in all months of the year */
int main()
{
  int rainfall[MONTHS];
  int i;
  for(i=0;i<MONTHS;i++){
    printf("Enter the rainfall(mm) of %d: ",i+1);scanf("%d",&rainfall[i]);
  }
  /*print from january to december*/
  printf("Detail\n");
  printf("Month\tRainfall\n");
  for (i=0;i<MONTHS;i++)
    printf("%d\t%5d\n",i+1,rainfall[i]);
  return 0;
}
