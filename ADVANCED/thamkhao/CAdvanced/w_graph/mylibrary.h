#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define max_library 100
//------------------------------------------------------------------------------------------
/* functions about string processing */
void clearBuff(){
	while(getchar()!='\n');
}
void trimRight(char a[]){
	int i=strlen(a)-1;
	while (i>=0) {
		if (a[i]!=' ') break;
		else a[i]='\0';
		i--;
	}
}
void deleteChar(char a[],int index){
	int i,n=strlen(a);
	if(index>=n) printf("The string has no element index %d\n",index);
	for (i=index;i<n;i++) a[i]=a[i+1];
}
void trimLeft(char a[]){
	int n=strlen(a);
	while(a[0]==' ') deleteChar(a,0);
}
void trimMid(char a[]){
	int i,k,n=strlen(a);
	for (i=0;i<n;i++){
		if (a[i]==' '){
			if (a[i+1]==' '){
				k=i;
				while(a[i]==' '){
					deleteChar(a,i);
					i=k+1;
				}
			}
		}
	}
}//-------------------------------------------------------------------------------------
void stringProcess(char a[]){
	int i;
	for(i=0;i<strlen(a);i++) 
		if (a[i]=='\t')	
		{
			/* code */
			deleteChar(a,i);
		}
	if(a[strlen(a)-1]=='\n') a[strlen(a)-1]='\0';
	trimRight(a);
	trimLeft(a);
	trimMid(a);
}
char *stringToUpper(char *s){
    int i=0;
    while(s[i]!='\0'){
        s[i]=toupper(s[i]);
        i++;
    }
    return s;
}
//------------------------------------------------------------------
//File functions
void fileCp(char *source,char*target){
	FILE *fin,*fout;
	int c;
	if ((fin=fopen(source,"r"))==NULL)	
	{
		printf("Cannot open %s to read\n",source);
		return;
	}
	else{
		if ((fout=fopen(target,"w"))==NULL)	
		{
			printf("Cannot open %s to write\n",target);
			return;
		}
		else{	
			fseek(fin,0,SEEK_SET);
			fseek(fout,0,SEEK_SET);
			while((c=fgetc(fin))!=EOF){
				fputc(c,fout);
			}
			fclose(fin);
			fclose(fout);
		}
		return;
	}
}
long unsigned int getSize(const char filename[]){
	long unsigned int size;
	FILE *fin;
	if ((fin=fopen(filename,"r"))==NULL)
	{
		printf("Cannot open %s to get size\n",filename);
		return 0;
	}else{
		rewind(fin);
		fseek(fin,0,SEEK_END);
		size=ftell(fin);
		return size;
	}
}
//------------------------------------------------------
//Menu functions
int getChoice(int firstChoice, int lastChoice){
    char c[2];
    int choice;
    do{
        scanf(" %[0-9]s",c);clearBuff();
        choice=atoi(c);
        if (choice<firstChoice||choice>lastChoice)
            {
                   printf("Invalid choice!\n");
            }
    }while(choice<firstChoice||choice>lastChoice);
    return choice;
}
//-------------------------------------------------------
//Standard phrase
int charnumber(char *s) {
  int i=0;
  while (s[i]!='\0') i++;
  return i;
}
void shiftleft(char *s, int n) {
  int i, max;
  max=charnumber(s);  
  for (i=n; i<max; i++) s[i]=s[i+1];
}
char *standadize(char *s) {
  int i=0, n, max;
  while (s[0]==' ') shiftleft(s, 0);
  max=charnumber(s);
  for (i=0; i<max; i++) {
    if (s[i]==' ' && s[i+1]==' ') {
      while (s[i+1]==' ') shiftleft(s, i+1);
    }
  }
  return s;
}
