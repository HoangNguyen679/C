#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

void doc_file();
int menu();

Graph g;

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
	    JRB tmp;
	    jrb_traverse(tmp,g.vertices)
	      printf("%s\n",getVertex(g,tmp->key.i));
	    // printf("\n");
	  } break;
	case 2:
	  {
	    getchar();
	    char str1[MAX],str2[MAX];
	    JRB check1,check2;
	    int id1,id2;
	    printf("Nhap ten ga di: ");scanf("%[^\n]",str1);
	    id1 = getID(g,str1); 
	    if(id1 == -1)
	      {
		printf("Khong co ga ho tro!\n");
		break;
	      }
	    getchar();
	    printf("Nhap ten ga den: ");scanf("%[^\n]",str2);
	    id2 = getID(g,str2);
	    if(id2 == -1)
	      {
		printf("Khong co ga ho tro!\n");
		break;
	      }

	    int path[MAX],i = 0;
	    double length[MAX];
	    memset(path,-1,sizeof(path));
	    memset(length,-1,sizeof(length));

	    shortest_path(g,id1,id2,path,length);
	    while(path[i] != -1)
	      printf("-->%s",getVertex(g,path[i++]));

	  } break;
	case 3:
	  printf("\nCam on ban da su dung chuong trinh\n\n");
	  return 0;
	default: printf("\nNhap sai!\n");
	}
    }
}

int menu()
{
  printf("\n\n------------METRO-----------\n\n");
  printf("1. Hien thi tat ca cac nha ga\n");
  printf("2. Tim duong di\n");
  printf("3. Thoat\n");
  printf("\nLua chon : ");
  int k; scanf("%d",&k);
  return k;
}

void doc_file()
{
  FILE *f = fopen("line.txt","r");
  if(!f)
    {
      printf("Loi mo file!\n");
      return;
    }
  char str[MAX];
  //  fgets(str,81,f);	  printf("%s ~~ %d\n",str,strcmp(str,"[STATIONS]"));
  fscanf(f,"%[^\n]\n",str);
  if(strcmp(str,"[STATIONS]") == 0)
    {
      while(1)
	{
	  fscanf(f,"%[^\n]\n",str);printf("%s\n",str);
	  if(strcmp(str,"[LINES]") == 0)
	    break;
	  // if(strcmp(str,"\n") == 0)
	  // continue;
	  //printf("%s\n",str);
	  int id;
	  char ten[MAX];
	  sscanf(str,"S%d=%[^\n]\n",&id,ten);
	  //printf("%d~~%s\n",id,ten);
	  addVertex(g,id,ten);
	}

       while(!feof(f))
      	{
	  fscanf(f,"%[^\n]\n",str);
	  printf("%s\n",str);
	  char str2[MAX],*p;
	  int v1,v2;
	  sscanf(str,"%*[^=]=%[^\n]\n",str2);
	  p = strtok(str2," ");
	  sscanf(p,"S%d",&v1);
	  p = strtok(NULL," ");
	  while(p != NULL)
	    {
	      sscanf(p,"S%d",&v2);
	      addEdge(g,v1,v2,1);
	      addEdge(g,v2,v1,1);
	      v1 = v2;
	      p = strtok(NULL," ");
	    }
	}
    }  
}
