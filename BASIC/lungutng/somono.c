// tim so môn, ma so môn la so khi gi :v
#include<stdio.h>
int soMono(int n)
{
  int i,a,io;
  a=n;
  if (a>0 && a<10) return 1;
  io = a % 10;
  while (a>0)
    {
      i = a % 10;
      if (i != io) return  0;
      a /= 10;
    }
  return 1;
}
main()
{
  int n;
  do
    {
      scanf("%d",&n);
      printf("%d\n",soMono(n));
    } while (n != 0);
}
