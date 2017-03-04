#include<stdio.h>
#include<string.h>
void mahoa(char s[], int k) {
	int i=0;
	while (s[i] != '\0') {
		if (s[i] >= 97 && s[i] <= 122) {
			if ((s[i]+k ) > 122) s[i] = s[i] + k - 122 + 97;
			else s[i] = s[i] + k ;
		}
		else if (s[i] >= 65 && s[i] <= 90) {
			if ((s[i] + k) > 90) s[i] = s[i] + k - 90 + 65;
			else s[i] = s[i] + k;
		}
		i++;
	}
}
void giaima(char s[], int k) {
	int i=0;
	while (s[i] != '\0') {
	if (s[i] >= 97 && s[i] <= 122) {
			if ((s[i] - k ) < 97) s[i] = s[i] - k + 122 - 97;
			else s[i] = s[i] - k ;
		}
	else if (s[i] >= 65 && s[i] <= 90) {
			if  ((s[i] - k) < 65) s[i] = s[i] - k + 90 - 65;
			else s[i] = s[i] - k;
	}
	i++;
}
}
main() {
	char s[100];
	int k;
    do {
      printf("Nhap k:");
      scanf("%d",&k);
      if (k<0) printf("Nhap lai (k>0) !\n");
    }
    while (k<0);
    k=k%26;
	getchar();
	gets(s);
	mahoa(s,k);
	puts(s);
	giaima(s,k);
	puts(s);
}
