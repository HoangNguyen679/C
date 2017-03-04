#include<stdio.h>
isLeafyear(int n)
{
	if (n%400==0 || n%4==0 && n%100!=0) return 1;
	else return 0;
}
main()
{
	int m,y;
	do {
      	    printf("Nhap vao nam: ");
	        scanf("%d",&y);
	        if (y<0) printf("Nhap lai (n>0): ");
        }
    while (y<0);
    do {
	        printf("Nhap vao thang: ");
	        scanf("%d",&m);
	        if (m<0) printf("Nhap lai\n");
       }
    while (m<0);
    switch (m) {
    	case 1:
    	case 3:
    	case 5:
    	case 7:
    	case 8:
    	case 10:
    	case 12: printf("Thang %d co 31 ngay\n",m);break;
    	case 4:
    	case 6:
    	case 9:
    	case 11: printf("Thang %d co 30 ngay\n",m);break;
    	case 2: if (isLeafyear(y)==1) printf("Thang %d co 29 ngay\n",m);
    }
}
