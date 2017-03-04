/* Nguyen Duc Hoang - 9A */
// Date Create: 25/03/2015
#include<stdio.h>
int main()
{
  int  m,y;
  printf("\n"); 
  printf("Nhap thang: ");
  scanf("%d",&m);
  printf("Nhap nam: ");
  scanf("%d",&y);
  printf("\n");
  switch (m)
    {
    case 1 :
    case 3 :
    case 5 :
    case 7 :
    case 8 : 
      printf("Thang %d co 31 ngay\n",m); break;
    case 4 :
    case 6 :
    case 9 :
    case 11:
      printf("Thang %d co 30 ngay\n",m); break;
    case 2 :
      {
	if (y % 4 == 2) {printf("Thang %d co 29 ngay\n",m); break;}
	else {printf("Thang %d co 28 ngay\n",m); break;}
      }
    default :
      printf("Khong hop le!\n");
    }
  printf("\n");
  return 0;
}
