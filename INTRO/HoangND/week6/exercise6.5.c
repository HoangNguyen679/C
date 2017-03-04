#include <stdio.h>
main()
{
  unsigned n,rd;
  printf("Guess my number (between 1 and 100): \n");
  scanf("%d",&n);
  srand((unsigned)time(NULL));
  rd= rand() %101;
  if (n >rd)
    printf("Your guess was too large\n");
  else if (n <rd)
    printf("Your guess was too small\n");
  else printf("You were correct!!\n");
  printf("The correct number was: %d\n",rd);
    }
  
