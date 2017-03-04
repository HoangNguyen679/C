/* Nguyen Duc Hoang - 9A */
// Date Create: 25/5/2015
#include<stdio.h>
#include<math.h>
int main() {
	long long n,t;
	long long j=0,i=2;
	scanf("%lld",&n);
	t=n;
	if (n == 1) printf("%d %d\n",1,1);
	while (t != 1) {
		while  (t % i == 0) {
			t/=i;
			j++;
		}
		if (j!=0) 	printf("%lld %lld\n",i,j);
		i++;j=0;
	}
	return 0;
}
