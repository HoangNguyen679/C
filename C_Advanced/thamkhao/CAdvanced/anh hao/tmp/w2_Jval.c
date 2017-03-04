#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_BUFF 512

typedef union
{
	int 	i;
	long 	l;
	float 	f;
	double 	d;
	void 	*v;
	char 	*s;
	char 	c;
} Jval;

Jval NewJval_i(int i)
{
	Jval temp;
	temp.i = i;
	return temp;
}

Jval NewJval_f(float f)
{
	Jval temp;
	temp.f = f;
	return temp;
}

Jval NewJval_d(double d)
{
	Jval temp;
	temp.d = d;
	return temp;
}

Jval NewJval_s(char *s)
{
	Jval temp;
	temp.s = (char*)malloc(sizeof(char)*MAX_BUFF);
	strcpy(temp.s, s);
	return temp;
}

int main(int argc, char const *argv[])
{
	Jval a;
	a = NewJval_s("12345678901234567890");
	printf("%s\n", a.s);	

	return 0;
}