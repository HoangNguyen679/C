/* Nguyen Duc Hoang - 9A */
// Date Create: 22/8/15
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 100
int main(int argc,char *argv[]){
if(argc == 2){
double e=1,y=1,x;
x = atof(argv[1]);
double saiso=0.00001;
int i=1;
do{
y*=x/i;
e=e+y;
i++;
} while(y>saiso);
printf("e^%g = %g\n\n",x,e);
}
else if(argc == 3){
double e=1,y=1,x,saiso;
int i=1;
x = atof(argv[1]);
saiso = atof(argv[2]);
do{
y*=x/i;
e=e+y;
i++;
} while(y>saiso);
printf("e^%g = %g\n\n",x,e);
}
else {
printf("Wrong argument!\n");
printf("Struc: ./filename number number or ./filename number!\n");
}
}
