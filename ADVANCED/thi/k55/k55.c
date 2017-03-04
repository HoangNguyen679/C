#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#define MAX 1000

Graph g;

int menu();
void doc_file();
void get_info();
void print_node(Graph g, int i);
void allIndegree(Graph g, int v, int *output);
void thoigian();

int main()
{
  g = createGraph();
  doc_file();
  while(1)
    {   
      switch(menu())
	{
	case 1:
	  {
	    int v = 0,e = 0;
	    JRB tmp,node,tree;
	    jrb_traverse(tmp,g.vertices)
	      v++;
	    jrb_traverse(tmp,g.edges)
	      {
		tree = (JRB)jval_v(tmp->val);
		jrb_traverse(node,tree)
		  e++;
	      }
	    
	    printf("\nSo dinh la : %d\n",v); 
	    printf("\nSo canh la : %d\n",e);
	  }break;
	case 2:get_info();break;
	case 3:
	  {
	    int output[MAX] = {};
	     allIndegree(g,5,output);
	    //  inDegree(g,5,output);
	    int q = 0;
	    while(output[q] != 0)
	      printf("%4d\t",output[q++]);
	    printf("\n");
	  }break;
	case 4:TSort(g,print_node);printf("\n");break;
	case 5:thoigian();break;
	case 6:
	  if(is_cyclic(g)) printf("\nDo thi co chu trinh!\n");
	  else printf("\nDo thi khong co chu trinh!\n");
	  break;
	case 7: return 0;
	default: printf("Nhap sai !\n\n");    
	}
    }
  
}

void print_node(Graph g, int i)
{
  printf("\t\t%s", getVertex(g, i));
}

int menu()
{
  printf("\n\n---------MENU---------\n\n");
  printf("1. Doc file\n");
  printf("2. Thong tin cong viec\n");
  printf("3. Yeu cau cong viec\n");
  printf("4. Thu tu topo\n");
  printf("5. Thoi gian toi thieu\n");
  printf("6. Kiem tra tinh hop le\n");
  printf("7. Thoat\n\n");
  printf("Please select: ");

  int k;scanf("%d",&k);
  return k;
}

void doc_file()
{
  FILE *f;
  char ten_file[MAX];
  
  //  getchar();
  // printf("Nhap ten file: ");
  // scanf("%[^\n]",ten_file);
  strcpy(ten_file,"a.txt");
  f = fopen(ten_file,"r");
  if(f == NULL)
    {
      printf("Loi mo file!\n");
      return;
    } 

  char s[MAX],tendinh[MAX],dulieu[MAX]={};
  while(1)
    {
      if( fgets(s,100,f) == NULL ) break;
      sscanf(s,"%[^ ] : %[^\n]",tendinh,dulieu);
    
      int v;
      sscanf(s,"A%d",&v);
      addVertex(g,v,tendinh);
     
      if(dulieu[0] == 'A')
	{
	  char *p = strtok(dulieu," ");
	  int v1;
	  double w;
       
	  while(p != NULL)
	    {
	      int i = 1,j = 0,k = 0;
	      char *tmp;
	      char str1[MAX],str2[MAX];
	      tmp = strdup(p);
	      while(tmp[i] != '-')
		str1[j++] = tmp[i++];
	      str1[j] = '\0';
	      i++;
	      while(tmp[i] != '\0' )
		str2[k++] = tmp[i++];
	      str2[k] = '\0';
	      v1 = atoi(str1);
	      w = atof(str2);
	      addEdge(g,v1,v,w);
	      p = strtok(NULL," ");
	    }
	} // het if
    } // het while (!feof)
}

void get_info()
{
  char congviec[MAX];getchar();
  printf("Nhap vao cong viec: ");scanf("%[^\n]",congviec);
  JRB tmp,tree,node;
  int check = 0,k, i, output[MAX] = {};
  jrb_traverse(tmp,g.vertices)
    if(strcmp(tmp->val.s,congviec) == 0)
      {
	check ++;
	k = inDegree(g,tmp->key.i,output);
      }
  if(check == 0)
    {
      printf("\n\nCong viec khong co trong chuong trinh!\n\n");
      return;
    }
    
  
  if(k == 0) printf("\nCong viec co the lam ngay\n");
  else
    {
      printf("\nSo luong cong viec ngay truoc: %d\n",k);
      printf("\nDanh sach: ");
      for(i = 0; i < k; i++)
	printf("%4s\t",getVertex(g,output[i]));
      printf("\n\n");
    }
}


void thoigian()
{
  char congviec[MAX];getchar();
  printf("Nhap vao cong viec: ");scanf("%[^\n]",congviec);
  JRB tmp;
  int check = 0;
  jrb_traverse(tmp,g.vertices)
    if(strcmp(tmp->val.s,congviec) == 0)
      check ++;
  if(check == 0)
    {
      printf("\n\nCong viec khong co trong chuong trinh!\n\n");
      return;
    }
  int output[MAX];
  double t,length[MAX];
  t = shortest_path(g,1,getID(g,congviec),output,length);
  printf("\nThoi gian toi thieu hoan thanh: %.1f \n",t);
  
}
