#include<stdio.h>
#include<string.h>
#include"lib_Tree.h"
int cmp(elementtype data1,elementtype data2)
{
  char tmp1[MAX],tmp2[MAX];
  int i;
  strcpy(tmp1,data1.tu);strcpy(tmp2,data2.tu);
  for(i=0;tmp1[i]!='\0';i++)
    if(tmp1[i]>='A'&&tmp1[i]<='Z') tmp1[i]+='a'-'A';
    for(i=0;tmp2[i]!='\0';i++)
    if(tmp2[i]>='A'&&tmp2[i]<='Z') tmp2[i]+='a'-'A';
    return strcmp(tmp1,tmp2);
}
void print(elementtype data)
{
  printf("%-15s:%s\n",data.tu,data.nghia);
}
void menu()
{
  printf("MENU\n1- Show\n");
  printf("2- Look up\n");
  printf("3- Insert new word\n");
  printf("4- Translate a sentence\n");
  printf("5- Fix word\n");
  printf("6- Exit\n");
  printf("============================================\n");
  printf("Press 0 to show menu\n");
}
node *get(FILE *f)
{
  elementtype data;
  node *tree=NULL;
  char ch;
  rewind(f);
  while(!feof(f))
    {
      fscanf(f,"%s",data.tu);
      fscanf(f,"%c",&ch);
      fscanf(f,"%[^\n]",data.nghia);
      if(!feof(f))
        tree=insert(tree,data);
    }
  return tree;
}
int trans(char word[],node *tree)
{
  elementtype data;
  node *tmp;
  strcpy(data.tu,word);
  if((tmp=search(tree,data))==NULL) return 0;
  else
    strcpy(word,tmp->data.nghia);
  return 1;
}
void update(FILE *f,node *tree)
{
  if(tree!=NULL)
    {
      update(f,tree->left);
      fprintf(f,"%s %s\n",tree->data.tu,tree->data.nghia);
      update(f,tree->right);
    }
}
void reset(elementtype *data)
{
  strcpy((*data).tu,"");
  strcpy((*data).nghia,"");
}
int main()
{
  FILE *f;
  int k,i,j;
  char filename[]="dict.txt",buff[MAX],word[MAX],new[MAX];
  elementtype data;
  node *tree=NULL,*tmp;
  if((f=fopen(filename,"r+"))==NULL)
    {printf("Cant open file %s\n",filename);exit(1);}
  else
    {
      printf("Menu:");
      tree=get(f);
      k=0;
      do{
        switch(k)
          {
          case 0: menu();break;
          case 1: show(tree,0);break;
          case 2:
            reset(&data);
            printf("Enter word you want to look up:");
            scanf("%[^\n]",buff);
            strcpy(data.tu,buff);
            if((tmp=search(tree,data))==NULL) printf("Cant find in this dictionary\n");
            else print(tmp->data);
            break;
          case 3:
            reset(&data);
            printf("Enter new word:");
            scanf("%s",buff);strcpy(data.tu,buff);
            while(getchar()!='\n');
            printf("Enter it's meaning:");
            scanf("%[^\n]",buff);strcpy(data.nghia,buff);
            tree=insert(tree,data);
            fprintf(f,"%s %s\n",data.tu,data.nghia);
            break;
          case 4:
            printf("Enter a sentence:");
            scanf("%[^\n]",buff);
            int n=strlen(buff),j;
            strcpy(new,"");
            for(i=0;i<n;i++)
              if(buff[i]>='A'&&buff[i]<='Z') buff[i]+='a'-'A';
            i=0;
            while(i<n)
              {
                while(buff[i]==' ') i++;
                j=i;
                strcpy(word,"");
                while((buff[i]<'a'||buff[i]>'z')&&buff[i]!=' '&&buff[i]!='\0')
                  {word[i-j]=buff[i];i++;}
                word[i-j]='\0';
                if(strcmp(word,"")==0)
                  {
                    while(buff[i]>='a'&&buff[i]<='z')
                      {word[i-j]=buff[i];i++;}
                    word[i-j]='\0';
                    if(trans(word,tree)==0)
                      {
                        while(getchar()!='\n');
                        printf("Enter \"%s\" 's meaning:",word);
                        scanf("%[^\n]",data.nghia);
                        strcpy(data.tu,word);
                        tree=insert(tree,data);
                        fprintf(f,"%s %s\n",data.tu,data.nghia);
                        strcpy(word,data.nghia);
                      }
                  }
                printf("%s\n",word);
                strcat(new,word);strcat(new," ");
              }
            printf("Sentence:%s\n",buff);
            printf("==>>>    %s\n",new);
            break;
          case 5:
            printf("Enter word you want to change meaning:");
            scanf("%s",word);
            while(getchar()!='\n');
            reset(&data);
            strcpy(data.tu,word);
            if((tmp=search(tree,data))==NULL)
              {
                printf("This is new word. Please insert first\n");
                printf("Its meaning:");scanf("%[^\n]",data.nghia);
                tree=insert(tree,data);
              }
            else
              {
                printf("Its meaning:");scanf("%[^\n]",data.nghia);
                strcpy(tmp->data.nghia,data.nghia);
                rewind(f);
                update(f,tree);
              }
            break;
          }
        scanf("%d",&k);
        while(getchar()!='\n');
      }while(k<6&&k>=0);
      fclose(f);
    }
  return 0;
}
