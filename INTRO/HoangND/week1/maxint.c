#include<stdio.h>
int MaxInt()
{
  int i,p=1;
  for(i=1;i<=31;++i)
    p=p*2;
  return(p);
}
main()
{
  printf("gia tri lon nhat la %d\n",MaxInt-1);
  return 0;
}
