/* Nguyen Duc Hoang - 9A */
// Date Create: 29/8/2015
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 81
enum{SUCCESS,FAIL};
void mahoacong(FILE *fptr,int dolech){
  int c;
  while((c=fgetc(fptr)) != EOF){
    if (c >= 97 && c <= 122) {
      if ((c+dolech ) > 122) c = c + dolech - 122 + 97;
      else c = c + dolech ;
      fputc(c,fptr);
    }
    else if (c >= 65 && c <= 90) {
      if ((c + dolech) > 90) c = c + dolech - 90 + 65;
      else c = c + dolech;
      fputc(c,fptr);
    }
    else fputc(c,fptr);
  }
}
int main(int argc,char *argv[]){
	if(argc != 3){
		printf("Wrong number of argument!\n");
		printf("Struct is ./filename tenfile dolechcong\n");
	}
	int reval = SUCCESS;
	FILE *f;
	char filename[MAX];
    int dolech;
    strcpy(filename,argv[1]);
    dolech = atoi(argv[2]);
	if((f=fopen(filename,"r+")) == NULL){
		printf("Cannot open %s\n",filename);
		reval = FAIL;
	}
    else {
      mahoacong(f,dolech);
      fclose(f);
    }
}
