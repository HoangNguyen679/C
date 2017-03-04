#include <iostream>

int n;
int a[1000];
long count;

void inkq(){
	count++;
	printf("the %ldth conf is: ", count);
	for (int i=1; i<=n; i++)
		printf("%d", a[i]);
	printf("\n");
}

void thugangiatri(int k){
	for (int val=0; val<=1; val++){
		a[k]=val;
		if (k==n) inkq();
		else thugangiatri(k+1);
	}
} //try value for variables a[k]

int main(){
	std::cout << "Nhap n = ";
	std::cin >> n;
	count = 0;
	thugangiatri(1);
	return 0;
}