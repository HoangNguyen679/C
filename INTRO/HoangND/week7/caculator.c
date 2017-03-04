/* Nguyen Duc Hoang - 9A */
// Date Create: 25/03/2015
#include<stdio.h>
int main()
{
  float a,b;
  char c;
  printf("Nhap vao phep toan:\n");
  scanf("%f",&a);
  c=getchar();
  scanf("%f",&b);printf("\n");
  switch (c)
    {
    case '+' :
      printf("%g + %g = %g\n",a,b,a+b); break;
    case '-' :
      printf("%g - %g = %g\n",a,b,a-b); break;
    case '*' :
      printf("%g * %g = %g\n",a,b,a*b); break;
    case '/' :
      {
	if (b==0) {printf("Khong hop le");break;}
	else {printf("%g / %g = %g\n",a,b,a/b); break;}
    case '^' :
      {
	int i,t=1;
	for(i=1;i<=b;i++) t=t*a;
	printf("%g ^ %g = %g\n",a,b,t);
      }
	break;
    default :
      printf("Khong hop le!\n");
    }
  printf("\n");
  return 0;
}
