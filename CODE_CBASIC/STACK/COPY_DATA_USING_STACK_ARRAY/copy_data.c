#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"stack_struct.h"

phone_address *add;

int main(){
  FILE *f1,*f2;
  char file1[]="phone_data.dat";
  char file2[]="phone_data_copy.dat";
  f1=fopen(file1,"rb");
  f2=fopen(file2,"wb");

  stack s=stackConstruct(&s);
  add = (phone_address *)malloc(sizeof(phone_address));
  while(fread(add,sizeof(phone_address),1,f1)) push(&s,*add);
  printStack(s);
  while(!isEmpty(s)){
    *add = pop(&s);
    fwrite(add,sizeof(phone_address),1,f2);
  }
  free(add);
  fclose(f1);fclose(f2);
  return 0;
}
