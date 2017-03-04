#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "undi_graph.h"
#define MAX 80

void printWay(int v2,int v1,int way[]);
void printVertex(int v);
char getMenu();
void clear_buffer();
void inputFromFile(char filename[]);
void checkLink();
void checkAdjacentVertex();
void findShortestWay();

Graph g;

int main(int argc, char *argv[])
{
  g = creatGraph();
  char filename[] = "sample.graph";
  char choice;

  while(1)
    {
      clear_buffer();
      choice = getMenu();
      switch(choice)
	{
	case '1': inputFromFile(filename);break;
	case '2': checkLink();break;
	case '3': checkAdjacentVertex();break;
	case '4': findShortestWay();break;
	case '5':
	  {
	    int v;printf("\n\nNhap dinh: ");scanf("%d",&v);
	    printf("\n\nDuong di: ");
	    BFS(g,v,-1,printVertex);printf("\n\n");
	  }break;
	case '6':
	  {
	    int v;printf("\n\nNhap dinh: ");scanf("%d",&v);
	    printf("\n\nDuong di: ");
	    DFS(g,v,-1,printVertex);printf("\n\n");
	  }break;
	case '7':
	  {
	    if(isCycle(g)) printf("\n\nDo thi co chu trinh\n\n");
	    else printf("\n\nDo thi khong co chu trinh\n\n");
	  }break;
	case '8':
	case '9':
	  {
	    //  dropGraph(&g);
	    return 0;
	  }
	default: printf("\n\nWrong choice!\n\n");
	  
	}
    }
 
}

void printWay(int v2,int v1,int way[])
{
  int u[100],v,x,i = 1,j;
  u[0] = v = x = v2;
  while(v != v1)
    {
      v = way[x];
      x = v;
      u[i++] = v;
    }
  for(j = i-1; j >= 0; j--)
    printf("%4d ",u[j]);     
}

void printVertex(int v)
{
  printf("%4d",v);
}

char getMenu()
{
  char choice;
  printf("---------------------------------------------------------------\n");
  printf("\t.=========================================.\n");
  printf("\t*    1. Nhap do thi                       *\n");
  printf("\t*    2. Kiem tra lien ket                 *\n");
  printf("\t*    3. Cac dinh ke                       *\n");
  printf("\t*    4. Duong di ngan nhat                *\n");
  printf("\t*    5. BFS                               *\n");
  printf("\t*    6. DFS                               *\n");
  printf("\t*    7. Kiem tra chu trinh                *\n");
  printf("\t*    8. Thanh phan lien thong             *\n");
  printf("\t*    9. Thoat                             *\n");
  printf("\t*=========================================*\n");
	
  printf("\t\tEnter your choice: ");
  choice = getchar();
  printf("---------------------------------------------------------------\n");

  return choice;
}

void clear_buffer()
{
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
}

void inputFromFile(char filename[])
{
  FILE *f = fopen(filename,"r");
  if(f == NULL)
    {printf("Failed open %s !\n",filename);return;}

  int l = 0,i,j;
  char s[MAX];
  while(fscanf(f,"%[^\n]\n",s) == 1) l++;
  rewind(f);
  int v[l];
  while(!feof(f))
    {
      for(i = 0; i < l; i++)
	{
	  for(j = 0; j < l; j++)
	    {
	      fscanf(f,"%d",&v[i]);
	      if(v[i] == 1) addEdge(g,i,j);
	    }
	  fscanf(f,"%[\n]",s);
	}
	
    }
  printf("\n\nNhap thanh cong\n\n");
  fclose(f);
}

void checkLink()
{
  int v1,v2;
  printf("\n\nNhap dinh 1: ");scanf("%d",&v1);
  printf("\n\nNhap dinh 2: ");scanf("%d",&v2);
  if(adjacent(g,v1,v2))
    printf("\n\nCo lien ket giua hai dinh %d va %d\n\n",v1,v2);
  else
    printf("\n\nKhong co lien ket giua hai dinh %d va %d\n\n",v1,v2);
}

void checkAdjacentVertex()
{
  int n,v,output[MAX],i;
  printf("\n\nNhap dinh can kiem tra: ");scanf("%d",&v);
  n = getAdjacentVertices(g,v,output);
  if(n == 0) return;
  printf("\n\nCac dinh ke voi dinh %d la: ",v);
  for(i = 0; i < n; i++)
    printf("%4d",output[i]);
  printf("\n\n");
}

void findShortestWay()
{
  int v1,v2,n;
  printf("\n\nNhap dinh dau: ");scanf("%d",&v1);
  printf("\n\nNhap dinh cuoi: ");scanf("%d",&v2);
  n = UShortestPath(g,v1,v2,printWay);
  if(n == -1) printf("\n\nNhap dinh khong hop le!");
  else printf("\n\nSo canh di qua: %d", n);
  printf("\n\n");
}
