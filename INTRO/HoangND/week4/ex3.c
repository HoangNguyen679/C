#include<stdio.h>
int main()
{
  char z[9] = { '\0' };
 printf("Enter a  string: ");
 scanf("%[^aeiou]",z);
 printf("the input was \"%s\"\n",z);
 return 0;
}
