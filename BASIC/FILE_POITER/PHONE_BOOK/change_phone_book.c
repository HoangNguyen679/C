#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 81

typedef struct phone_address{
  char name[25];
  char tel[12];
  char email[25];
}phone_address;

char filedat[]="phone_data.dat";
char filetext[]="phone_data.txt";
FILE *f_dat,*f_txt;

int main(){
  phone_address *phone;
  if((f_txt=fopen(filetext,"r+")) == NULL){printf("Cannot open %s\n",filetext); return 1;}
  if((f_dat=fopen(filedat,"w+b")) == NULL){printf("Cannot open %s\n",filedat); return 1;}
  char str[MAX]; int n=0,i;
  while(fgets(str,MAX,f_txt) != NULL) n++;
  rewind(f_txt);
  phone = (phone_address *)malloc(n*sizeof(phone_address));
  for(i = 0; i < n; i++){
    fscanf(f_txt,"%s",(phone+i)->name);
    fscanf(f_txt,"%s",(phone+i)->tel);
    fscanf(f_txt,"%s",(phone+i)->email);
  }
  fwrite(phone,sizeof(phone_address),n,f_dat);
  free(phone);
  fclose(f_txt);
  fclose(f_dat);
}
