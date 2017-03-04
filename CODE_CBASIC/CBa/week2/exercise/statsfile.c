/* Nguyen Duc Hoang - 9A */
// Date Create: 29/8/2015
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 81
enum{SUCCESS,FAIL};

int main(int argc,char *argv[]){
	if(argc != 2){
		printf("Wrong number of argument!\n");
		printf("Struct is ./filename filenametxt\n");
	}
	int reval = SUCCESS;
	FILE *f;
	char filename[MAX];
	strcpy(filename,argv[1]);

	if((f=fopen(filename,"r")) == NULL){
		printf("Cannot open %s\n",filename);
		reval = FAIL;
	}
	FILE *fpr;
	char filename1[]="sourestats.txt";
	if((fpr=fopen(filename1,"w")) == NULL){
		printf("Cannot open %s\n",filename1);
		reval = FAIL;
	}
	int count[MAX];
    int i;
    for(i=0;i<MAX;i++) count[i]=0;
	int c;
	while((c=fgetc(f)) != EOF){
		if(isalpha(c)){
          if(isupper(c)){
            tolower(c);
            count[c-97]++;
          }
          else count[c-97]++;
		}
	}
	for(i=0;i<26;i++){
		if(count[i] != 0){
			printf("Character %c appears %d times\n",i+97,count[i]);
			fprintf(fpr,"Character %c appears %d times\n ",i+97,count[i]);
		}
	}
    return reval;
}
