/* Nguyen Duc Hoang - 9A */
// Date Create: 25/03/2015
#include<stdio.h>
int main()
{
  int a; 
  printf("1. Input Expression\n");
  printf("2. Dislay Result\n");
  printf("3. Quit\n");
  printf("Select a choice ( 1 or 2 or 3): ");
  scanf("%d",&a);
  switch (a)
    {
    case 1: printf("Input Expession\n"); break;
    case 2: printf("Display Result\n"); break;
    case 3: printf("Quit\n"); break;
    default: printf("Khong hop le");
    }
  return 0;
}
