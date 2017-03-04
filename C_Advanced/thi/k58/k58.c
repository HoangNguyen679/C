#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int doc_dothi(Graph, char*);
int parse_int(char* arg, int* out);
void print_node(Graph g, int i);
  
Graph g;

int main(int argc, char*argv[])
{
    
  if(argc == 1 || (strcmp(argv[1], "help") == 0 && argc == 2))
    {
      printf("\nSupported command: help, i2n, n2i, cc, cr, odg, rel.\n\n");
    }
  else if(argc == 2 && strcmp(argv[1], "about") == 0)
    {
      printf("\nC advanced 20142 final exam\n\n");
    }
  else if(argc == 4 && strcmp(argv[1], "i2n") == 0)
    {
      g = createGraph();
      int id;
      char *name;
      if(doc_dothi(g,argv[2]) && parse_int(argv[3],&id))
	if((name = getVertex(g,id)) != NULL)
	  printf("%s\n",name);	
    }
  else if(argc == 4 && strcmp(argv[1], "n2i") == 0)
    {
      g = createGraph();
      int id;
      char *name;
      if(doc_dothi(g,argv[2]))
	if((id = getID(g,argv[3])) != -1)
	  printf("%d\n",id);
    }
  else if(argc == 5 && strcmp(argv[1], "cc") == 0)
    {
      g = createGraph();
      int id1,id2,n1,i,j;
      int output1[MAX];
      char *name;
      memset(output1,-1,sizeof(output1));
 
      if(doc_dothi(g,argv[2]) && parse_int(argv[3],&id1)
	 &&  parse_int(argv[4],&id2))
	{
	  n1 = outDegree(g,id1,output1);
	  for(i = 0; i < n1; i++)
	    if(adjacent(g,id2,output1[i]))
	      printf("%s\n",getVertex(g,output1[i]));
	}
    }
   else if(argc == 5 && strcmp(argv[1], "cr") == 0)
    {
      g = createGraph();
      int id1,id2,n1,i;
      int output1[MAX];
      char *name;
      memset(output1,-1,sizeof(output1));
 
      if(doc_dothi(g,argv[2]) && parse_int(argv[3],&id1)
	 &&  parse_int(argv[4],&id2))
	{
	  n1 = inDegree(g,id1,output1);
	  for(i = 0; i < n1; i++)
	    if(adjacent(g,output1[i],id2))
	      printf("%s\n",getVertex(g,output1[i]));
	}
    }
   else if(argc == 4 && strcmp(argv[1], "odg") == 0)
    {
      g = createGraph();
      int id1,n1,i,k;
      JRB tmp;
      int output1[MAX];
      memset(output1,-1,sizeof(output1));
 
      if(doc_dothi(g,argv[2]) && parse_int(argv[3],&k))
	jrb_traverse(tmp,g.vertices)
	  {
	    n1 = outDegree(g,tmp->key.i,output1);
	    if(n1 > k)
	      printf("%s\n",tmp->val.s);
	  }
    }
   else if(argc == 4 && strcmp(argv[1], "rel") == 0)
     {
       g = createGraph();
       int id1,n1,n2,i,j,u;
       int output1[MAX],output2[MAX];
       JRB tmp;
       memset(output1,-1,sizeof(output1));
       memset(output2,-1,sizeof(output2));
       if(doc_dothi(g,argv[2]) && parse_int(argv[3],&u))
	 {
	   n1 = outDegree(g,u,output1);
	   for(i = 0; i < n1; i++)
	     {
	       printf("%s\n",getVertex(g,output1[i]));
	       n2 = outDegree(g,output1[i],output2);
	       for(j = 0; j < n2; j++)
		 printf("%s\n",getVertex(g,output2[j]));
	     }
	 }
     }
   else
     printf("Cau lenh khong duoc ho tro.\n");

  return 0;
}

int doc_dothi(Graph g, char* file_name)
{
  FILE *f = fopen(file_name,"r");
  if(!f)
    return 0;
  int n,m,i,u,v1,v2;
  char tmp[MAX];
  fscanf(f,"%d %d",&n,&m);
  for(i = 0; i < n; i++)
    {
      fscanf(f,"%s %d",tmp,&u);
      addVertex(g,u,tmp);
    }
  for(i = 0; i < m; i++)
    {
      fscanf(f,"%d %d",&v1,&v2);
      addEdge(g,v1,v2,1);
    }
  fclose(f);
  return 1;
}

int parse_int(char* arg, int* out)
{
  return sscanf(arg, "%d", out);
}

void print_node(Graph g, int i)
{
  printf("\t\t%s", getVertex(g,i));
}
