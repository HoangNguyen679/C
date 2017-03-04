#include <stdio.h>
#include <time.h>

void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}

int main ()
{
  int n;
  printf ("Starting countdown...\n");
  for (n=10; n>0; n--)
  {
    printf ("%d\n",n);
    wait (1);
  }
  printf ("FIRE!!!\n");
  return 0;
}
