#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void gen_qsort(
	void* buf,
	int num,
	int size,
	int (*cmp_fn)(void const*, void const*)
);

int int_cmp(void const*, void const*);
int float_cmp(void const*, void const*);
int str_cmp(void const*, void const*);

int main(int argc, char const *argv[])
{
	/*float numAr[10];

	srand(time(NULL));

	int i;
	for(i = 0; i < 10; i++) {
		numAr[i] = rand()%9*0.1+rand()%5;
		printf("%.2f  ", numAr[i]);
	}
	printf("\n");

	printf("After sort:\n");
	gen_qsort(numAr, 10, sizeof(int), float_cmp);
	for(i = 0; i < 10; i++)
		printf("%.2f  ", numAr[i]);
	printf("\n");*/

	char nameList[5][20];

	strcpy(nameList[0],"Hoang Anh");
	strcpy(nameList[1],"Hoang Giang");
	strcpy(nameList[2],"Hoang Hoa");
	strcpy(nameList[3],"Truong An");
	strcpy(nameList[4],"Viet Dung");

	gen_qsort(nameList, 5, 20*sizeof(char), str_cmp);
	int i;
	for(i = 0; i < 5; i++)
		printf("%s\n", nameList[i]);
	printf("\n");

	return 0;
}


void gen_qsort(
	void* buf,
	int num,
	int size,
	int (*cmp_fn)(void const*, void const*))
{
	char *_buf = (char*)buf;
	int L, R, mid;
	int i;

	while(num > 1){
		L = 0;
		R = num-1;
		mid = (L + R)/2;

		while(1){
			while(cmp_fn(&_buf[size*mid], &_buf[size*L])>0){
				L++;
			}
			while(cmp_fn(&_buf[size*mid], &_buf[size*R])<0)
				R--;
			if(L >= R) break;
			for(i = 0; i < size; i++){
				char tmp = _buf[size*L+i];
				_buf[size*L+i] = _buf[size*R+i];
				_buf[size*R+i] = tmp;
			}
			if(mid == L) mid = R;
			else if(mid == R) mid = L;
			L++;
			R--;
		}
		R++;
		if(R < num-R){
			qsort(_buf, R, size, cmp_fn);
			_buf = &_buf[size*R];
			num = num - R;
		}
		else{
			qsort(&_buf[size*R], num-R, size, cmp_fn);
			num = R;
		}
	}
}

int int_cmp(void const* x, void const* y){
	int a = *((int*)x);
	int b = *((int*)y);

	if(a == b) return 0;
	return a > b ? 1 : -1;
}

int float_cmp(void const* x, void const* y){
	float a = *((float*)x);
	float b = *((float*)y);

	if(a == b) return 0;
	return a > b ? 1 : -1;	
}

int str_cmp(void const* str_1, void const* str_2){
	char* first_str = (char*)str_1;
	char* second_str = (char*)str_2;

	if(!strcmp(first_str, second_str)) return 0;
	else if(strcmp(first_str, second_str) < 0) return -1;
	else return 1;
}
