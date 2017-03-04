#include <iostream>
#define MAXN 100
int d[MAXN][MAXN];
int init(){
	for (int i = 0;i<MAXN;i++){
		d[i][0] = 1;
		d[i][i] = 1;
	}
	for (int i = 0;i<MAXN;i++)
		for (int j = i+1;j<MAXN;j++)
			d[i][j] = -1;
}
int c(int i, int j){
	if (d[i][j] != 0) return (d[i][j]);
	d[i][j] = c(i-1,j-1)+c(i-1,j);
	return(d[i][j]);
}
int main(){
	int n,k;
	std::cin>> n >> k;
	init();
	std::cout  << c(n,k);
}