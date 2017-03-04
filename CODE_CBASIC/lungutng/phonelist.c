#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct {
  char name[30];
  char tel[12];
  char email[30];
}address;
struct list_el{
  struct list_el *next;
  address addr;
};
typedef struct list_el node_addr;
node_addr *root=NULL,
  *cur=NULL,
  *prev=NULL;
node_addr *makeNewNode(address addr){
  node_addr *new=(node_addr *)malloc(sizeof(node_addr));
  new->addr=addr;
  new->next=NULL;
  cur=new;
  return new;
}
node_addr *insertFirst(address addr){
  node_addr *new=makeNewNode(addr);
  new->addr=addr;
  new->next=root;
  root=new;
  cur=new;
  return new;
}
void readNode(FILE *f,address tmp){
  while(feof(f) ==0){
    fread(&tmp,sizeof(address),1,f);
    insertFirst(tmp);
  }
}
void printNode(node_addr *p){
    for(p;p!=NULL;p=p->next)
      printf("%-30s\t%-12s\t%-30s\n",(p->addr).name,(p->addr).tel,(p->addr).email);
}
int main(){
  FILE *f;
  char filename[]="phonebook.dat";
  if((f=fopen(filename,"rb")) == NULL){
    printf("Cannot open %s\n",filename);
    return 1;
  }
  address tmp;
  readNode(f,tmp);
  printNode(root);
  fclose(f);
  return 0;
}
