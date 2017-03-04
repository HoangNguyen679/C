#include<stdio.h>
char getachar(char c)
{
	printf("Nhap vao ki tu: ");
	c=getchar();
	if ((c>='A'&&c<='z')||(c>='0'&&c<='9')) return c;
	else return '#';
	
}
main()
{
	int i=1;
	char c,d;
	d=getachar(c);
	while (d=='#')
	{
		printf("ERROR\n");
		d=getachar(c);
		if (i>3) {
			printf("Ban da nhap qua 3 lan!\n");
			break;
		}
		i++;
	}
}