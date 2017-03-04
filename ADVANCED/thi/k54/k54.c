#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ind_graph.h"

int menu();
void doc_mecung();
void sodinh_socanh();
void in_dinhke();
void duongdi_ngannhat();
void reverse(char s[]);
char * itoa(int n, char s[]);
void duong_thoat();
void BFS_C(Graph g,int start,int stop,int *output,int *n);
void lien_thong();

Graph g;
int line;

int  main()
{
  g = createGraph();
  while(1)
    {
      switch(menu())
	{
	case 1:doc_mecung();break;
	case 2:sodinh_socanh();break;
	case 3:in_dinhke();break; 
	case 4:duongdi_ngannhat();break;
	case 5:duong_thoat();break;
	case 6:lien_thong();break;
	case 7: return 0;
	default: printf("\n\nNhap sai!\n\n");
	}
    }
}

int menu()
{
  printf("\n\n----------MENU---------\n\n");
  printf("1. Doc me cung\n");
  printf("2. Tong so dinh va tong so canh\n");
  printf("3. In dinh ke\n");
  printf("4. Duong di ngan nhat \n");
  printf("5. Tim duong thoat\n");
  printf("6. Thanh phan lien thong lon nhat\n");
  printf("7. Thoat\n");
  printf("\n\nPlease select:  ");
  int k; scanf("%d",&k);
  return k;
}

void doc_mecung()
{
  char filename[] = "mecung.txt";
  FILE *f = fopen(filename,"r");
  if(!f)
    {
      printf("\n\nLoi doc file!\n\n");
      return;
    }
  int i,j,temp[100],dinh = 0;
  char str[100],buff1[100],buff2[100];
  line = 0;
  while(fgets(str,81,f)) line++;
  rewind(f);
  
  int a[line][line];
  for(i = 0; i < line; i++)
    for(j = 0; j < line; j++)
      {
	fscanf(f,"%d",&a[i][j]);
	if(a[i][j] == 0)
	  {
	    char value[100] = {};
	    strcat(value,itoa(i,buff1));
	    strcat(value,itoa(j,buff2));
	    addVertex(g,i*line+j,value);
	  }
      }

  printf("\n\n");
  for(i=0;i<line;i++)
    {
      for(j=0;j<line;j++)
	printf("%2d",a[i][j]);
      printf("\n");
    }
  for(i = 0; i < line; i++)
    for(j = 0; j < line - 1; j++)
      {
	 if(a[i][j]==0 && a[i][j+1]==0)
	   addEdge(g,i*line+j,i*line+j+1,1);
	 
	 if(a[j][i]==0 && a[j+1][i]==0)	   
	   addEdge(g,j*line+i,(j+1)*line+i,1);
      }
}

void reverse(char s[])
{
  int i, j;
  char c;
  
  for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
     }
}

char * itoa(int n, char s[])
{
  int i, sign;
  
  if ((sign = n) < 0)  /* record sign */
    n = -n;          /* make n positive */
  i = 0;
  do
    {       /* generate digits in reverse order */
      s[i++] = n % 10 + '0';   /* get next digit */
    }
  while ((n /= 10) > 0);     /* delete it */

  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
  return s;
}

void sodinh_socanh()
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
  printf("\n\n");
  printf("So dinh la : %d\n\n",v); 
  printf("So canh la : %d\n\n",e/2); 
}

void in_dinhke()
{
  char str[100];
  getchar();
  printf("Nhap ten dinh: ");
  scanf("%[^\n]",str);

  JRB tmp;
  int check = 0,i = 0,k,output[100];
  memset(output,-1,sizeof(output));
  jrb_traverse(tmp,g.vertices)
    {     
      if(strcmp(tmp->val.s,str) == 0)
	{
	  check ++;	 
	  k = outDegree(g,tmp->key.i,output);
	}
    }
  
  if(check == 0)
    {
      printf("\nDinh nhap vao khong hop le!\n");
      return;
    }
    
  printf("Nhung dinh ke voi dinh %s : ",str);
  for(i = 0; i < k ; i++)
    printf("%s\t",getVertex(g,output[i]));
}

void duongdi_ngannhat()
{
  
  getchar();
  char str1[100],str2[100];
  JRB tmp;
  int check = 0;
  printf("Nhap ten dinh 1: ");
  scanf("%[^\n]",str1);
  jrb_traverse(tmp,g.vertices)
    if(strcmp(tmp->val.s,str1) == 0)
      check++;
  if(check == 0)
    {
      printf("\nDinh nhap vao khong hop le!\n");
      return;
    }
  
  getchar();
  check = 0;
  printf("Nhap ten dinh 2: ");
  scanf("%[^\n]",str2);
  jrb_traverse(tmp,g.vertices)
    if(strcmp(tmp->val.s,str2) == 0)
      check++;
  if(check == 0)
    {
      printf("\nDinh nhap vao khong hop le!\n");
      return;
    }
  
  int path[MAX];
  double length[MAX];
  memset(path,-1,sizeof(path));
  memset(length,-1,sizeof(length));

  printf("\n\n");
  shortest_path(g,getID(g,str1),getID(g,str2),path,length);
  int i = 0;
  while(path[i] != -1)
    printf("%s\t",getVertex(g,path[i++]));

}

void duong_thoat()
{
  getchar();
  char str[100];
  JRB tmp;
  int check = 0,check2 = 0,id,i;
  printf("Nhap ten dinh : ");
  scanf("%[^\n]",str);
  jrb_traverse(tmp,g.vertices)
    if(strcmp(tmp->val.s,str) == 0)
      check++;
  
  if(check == 0)
    {
      printf("\nDinh nhap vao khong hop le!\n");
      return;
    }
  id = getID(g,str);
  if(id < line || id > line*(line -1))
    check2++;
  else
    {
      for(i = 1; i < line -1; i++)
	if(id == (i*line) || id == (i*line+line-1))
	  check2++;
    }
 
   if(check2 == 0)
    {
      printf("\nDinh nhap vao khong hop le!\n");
      return;
    }

   int visited[MAX],parent[MAX];
   int u,v,n,output[MAX];
   int t = -1;
   memset(visited,0,sizeof(visited));
   memset(parent,-1,sizeof(parent));

   Dllist queue,node;
   queue = new_dllist();
   dll_append(queue,new_jval_i(id));
   while(!dll_empty(queue))
     {
       node = dll_first(queue);
       u = node->val.i;
       dll_delete_node(node);
       if(!visited[u])
	 {
	   visited[u] = 1;
	   if(u != id && (u/line == 0 || u%line == 0 || u%line == (line-1) || u/line > line*(line-1)))
	     {
	       t = u;
	       break;
	     }
	   n = outDegree(g,u,output);
	   for(i = 0; i < n; i++)
	     {
	       v = output[i];
	       if(!visited[v])
		 {
		   parent[v] = u;
		   dll_append(queue,new_jval_i(v));
		 }
	     }
	 }
     }

   if(t == -1)
     {
       printf("Khong co duong thoat\n");
       return;
     }

   Dllist list = new_dllist();
   u=t;
   while(u != -1)
     {
       dll_append(list,new_jval_i(u));
       v=parent[u];
       u=v;
     }
   printf("\nDuong thoat la: ");
   dll_rtraverse(node,list)
     printf("%s\t",getVertex(g,node->val.i));
   
}

void lien_thong()
{
  int visited[MAX],output[MAX],temp[MAX];
  int u,v,i,n,max = 0;
  JRB tmp;
  memset(visited,0,sizeof(visited));

  jrb_traverse(tmp,g.vertices)
    {
      u = tmp->key.i;
      if(!visited[u])
	{
	  BFS_C(g,u,-1,temp,&n);
	  if(n > max)
	    {
	      max = n;
	      memcpy(output,temp,max*sizeof(int));
	    }
	}
    }

  printf("Thanh phan lien thong lon nhat: ");
  for(i = 0; i < max; i++)
    printf("%s\t",getVertex(g,output[i]));
  
}

void BFS_C(Graph g,int start,int stop,int *output,int *n)
{
  *n=0;
  int i,m,visited[MAX];
  int u,v,tmp[MAX];
  Dllist queue,node;
  memset(visited,0,sizeof(visited));
  queue = new_dllist();
  dll_append(queue,new_jval_i(start));
  while(!dll_empty(queue))
    {
      node = dll_first(queue);
      u = node->val.i;
      dll_delete_node(node);
      if(!visited[u])
	{
	  output[(*n)++] = u;
	  visited[u] = 1;
	  if(u == stop) return ;
	  m = outDegree(g,u,tmp);
	  for(i = 0; i < m; i++)
	    {
	      v = tmp[i];
	      if(!visited[v])
		dll_append(queue,new_jval_i(v));
	    }
	}
    }
}
