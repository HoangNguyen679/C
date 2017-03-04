#include<stdio.h>
void printBinary(int n)
{
  int i=1,du=0,th;
  th=n;
  while (th>0){
    du+=i*(th%2);
    th=th/2;
    i*=10;
  }
  printf("Binary is: %d\n",du);
}
void printOctal(int n)
{
  int i=1,du=0,th;
  th=n;
  while (th>0){
    du+=i*(th%8);
    th=th/8;
    i*=10;
  }
  printf("Octal is: %d\n",du);
}
void printHexa(int n)
{
  int i=0,j=0,th;
  char s[100];
  th=n;
  while (th>0){
  	s[i]=th%16;
    th=th/16;
    i++;
  }
  printf("Hexa is: ");
  for (j=i;j>=0;j--)
  {
  	if (s[j]<10) printf ("%d",s[j]);
  	switch (s[j]) {
    case 10:printf("A");break;
    case 11:printf("B");break;
    case 12:printf("C");break;
    case 13:printf("D");break;
    case 14:printf("E");break;
    case 15:printf("F");break;
    	}
	}
	printf("\n");
}
main()
{
  int n;
  printf("Nhap vao mot so: ");
  scanf("%d",&n);
  printBinary(n);
  printOctal(n);
  printHexa(n);
}



