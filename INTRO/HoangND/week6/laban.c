/* Nguyen Duc Hoang - 9A */
// Date Create: 25/3/2015
#include<stdio.h>
#include<math.h>
int main()
{
	float x,y,a,b,s;
	printf("Nhap vao toa do cua ban:\n");
	printf("Nhap vao hoanh do: ");
	scanf("%f",&x);
	printf("Nhap vao tung do: ");
	scanf("%f",&y);
	printf("Nhap vao toa do dich can den:\n");
	printf("Nhap vao hoanh do dich den: ");
	scanf("%f",&a);
	printf("Nhap vao tung do dich den: ");
	scanf("%f",&b);
	if (x==0 && y>0) printf("Ban dang o huong bac");
	else if (x==0 && y==0) printf("Ban dang o trung tam ban do");
	else if (x==0 && y<0) printf("Ban dang o huong nam");
	else if (y==0 && x>0) printf("Ban dang o huong dong");
	else if (y==0 && x<0) printf("Ban dang o huong tay");
	else if (x>0 && y>0) printf("Ban dang o huong dong bac");
	else if (x<0 && y>0) printf("Ban dang o huong tay bac");
	else if (x>0 && y<0) printf("Ban dang o huong dong nam");
	else printf("Ban dang o huong tay nam");
	printf("\n");
	s=sqrt((x-a)*(x-a)+(y-b)*(y-b));
	printf("Khoang cach den dich den la: %g\n",s);
	return 0;
}
