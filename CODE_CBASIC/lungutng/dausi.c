/* Nguyen Duc Hoang - 9A */
// Date Create: 31/5/15
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
void clear_buffer() {
	int ch;
	while((ch=getchar()) != '\n' && ch != EOF);
}
typedef struct {
	char ten[30];
	float sucmanh;
	float nhanhnhen;
	float mau;
}dauSi;
dauSi arena(dauSi a,dauSi b) {
	float trungbinha,trungbinhb;
	int *ngaunhien;
	srand((unsigned)time(NULL));
	trungbinha = a.sucmanh + a.nhanhnhen + a.mau;
	trungbinhb = b.sucmanh + b.nhanhnhen + b.mau;
	if (trungbinha>trungbinhb) {
		a.sucmanh+=0.02 * (a.sucmanh);
		a.nhanhnhen+=0.02 * (a.nhanhnhen);
		a.mau+= 0.02 * (a.mau);
		b.sucmanh+=0.01 * (b.sucmanh);
		b.nhanhnhen+=0.01 * (b.nhanhnhen);
		b.mau+= 0.01 * (b.mau);
		return a;
	}
	if (trungbinha<trungbinhb) {
		b.sucmanh+=0.02 * (b.sucmanh);
		b.nhanhnhen+=0.02 * (b.nhanhnhen);
		b.mau+= 0.02 * (b.mau);
		a.sucmanh+=0.01 * (a.sucmanh);
		a.nhanhnhen+=0.01 * (a.nhanhnhen);
		a.mau+= 0.01 * (a.mau);
		return b;
	}
}
main() {
	dauSi dausi[3],c;
	int i=0;

	while (i<3){
		printf("Nhap ten dau si %d: ",i+1); gets(dausi[i].ten);
		printf("Suc manh: ");scanf("%f",&dausi[i].sucmanh);
		printf("Nhanh nhen: ");scanf("%f",&dausi[i].nhanhnhen);
		printf("Mau: ");scanf("%f",&dausi[i].mau);clear_buffer();
		i++;
	}
	c = arena(dausi[0],dausi[1]);
	printf("%s",arena(dausi[0],dausi[1]).ten);

}
