/* Nguyen Duc Hoang - 9A */
// Date Create:9/3/2015
#include<stdio.h>
int main()
{
  int qty,price,total,vat;
  char ISBN[20],Tit[30];
  printf("Enter title : ");
  gets(Tit);
  printf("Enter quantity: ");
  scanf("%d",&qty);
  printf("Enter Price: ");
  scanf("%d",&price);
  printf("Enter ISBN: ");
  scanf("%s",ISBN);
  getchar();
  total = qty * price;
  vat = total *4 / 100;
	printf("                                             \n");
	printf("      BK Bookseller                          \n");
	printf(" %-3s \t %-20s \t %-30s \t %-10s \t %-10s    \n","Qty","ISBN","Title","Price","Total");
	printf("--------------------------------------------------------------------------------------------------\n");
	printf(" %-3d \t %-20s \t %-30s \t %-10d \t %-10d    \n",qty,ISBN,Tit,price,total);
	printf("                                             \n");
	printf(" VAT:%d x 4%% =  %d                          \n",total,vat);
	printf(" You pay: %d                                 \n",total+vat);
	printf("__________________________________________________________________________________________________\n");
    return 0;
}
