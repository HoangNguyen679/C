#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int parse_int(char* arg, int* out);
void print_node(Graph g, int i);
int doc_dothi(Graph g, char* file_name);
  
Graph g;

int main(int argc,char *argv[])
{
  if(argc == 2 && strcmp(argv[1], "-h") == 0)
    {
      printf("C-Advanced, HK20152\n");
    }
  else if(argc == 3 && strcmp(argv[1],"-v") == 0 )
    {
      g = createGraph();
      if(doc_dothi(g,argv[2]))
	{
	  JRB tmp;
	  jrb_traverse(tmp,g.vertices)
	    printf("%d %s\n",tmp->key.i,getVertex(g,tmp->key.i));
	}
    }
  else if(argc == 5 && strcmp(argv[1],"-w") == 0)
    {
      g = createGraph();
      int id1,id2;
       if(doc_dothi(g,argv[2]) && parse_int(argv[3],&id1) && parse_int(argv[4],&id2))
	 {
	   if(!adjacent(g,id1,id2))
	     printf("-1\n");
	   else
	     printf("%d\n",getEdgeValue(g,id1,id2));
	 }
      
    }
  else if(argc == 5 && strcmp(argv[1],"-p") == 0)
    {
      g = createGraph();
      int id1,id2;
      if(doc_dothi(g,argv[2]) && parse_int(argv[3],&id1) && parse_int(argv[4],&id2))
	{
	  int path[MAX];
	  int length[MAX];
	  int x,i = 0;
	  memset(path,-1,sizeof(path));
	  memset(length,-1,sizeof(length));
	  x = shortest_path(g,id1,id2,path,length);
	  if(x == INFINITY) return;
	  printf("%d\n",x);
	  while(path[i] != -1)
	    {
	      printf("%s\n",getVertex(g,path[i++]));
	    }
	}
      
    }
  else if(argc == 4 &&strcmp(argv[1],"-n") == 0)
    {
      g = createGraph();
      int id;
      if(doc_dothi(g,argv[2]) && parse_int(argv[3],&id))
	{
	  int out,i;
	  int output[MAX];
	  memset(output,-1,sizeof(output));
	  out = outDegree(g,id,output);
	  printf("%d\n",out);
	  for(i = 0; i < out; i++)
	    printf("%d %s %d\n",output[i],getVertex(g,output[i])
		   ,getEdgeValue(g,id,output[i]));
	}
    }
  else if(argc >= 4 && strcmp(argv[1],"-s") == 0)
    {
      g = createGraph();
      if(doc_dothi(g,argv[2]))
	{
	  int n = argc - 3;
	  int id[n],i,j;
	  for(i = 0; i < n; i++)
	    {
	      if(!parse_int(argv[i+3],&id[i]))
		return;
	    }
	  
	  Graph new = createGraph();
	  JRB temp;
	  for(i = 0; i < n; i++)
	    {
	      temp = jrb_find_int(g.vertices,id[i]);
	      if(temp != NULL)
		addVertex(new,id[i],getVertex(g,id[i]));
	    }
	  for(i = 0; i < n; i++)
	    for(j = 0; j < n; j++)
	      {
		if(adjacent(g,id[i],id[j]))
		  {
		    addEdge(new,id[i],id[j],getEdgeValue(g,id[i],id[j]));
		    addEdge(new,id[j],id[i],getEdgeValue(g,id[j],id[i]));
		  }
		
	      }
	  int v = 0,e = 0;
	  JRB tmp,node,tree;
	  jrb_traverse(tmp,new.vertices)
	    v++;
	  jrb_traverse(tmp,new.edges)
	    {
	      tree = (JRB)jval_v(tmp->val);
	      jrb_traverse(node,tree)
		e++;
	    }
	  e = e/2;
	  
	  printf("%d\n",v);
	  jrb_traverse(tmp,new.vertices)
	    printf("%d %s\n",tmp->key.i,getVertex(new,tmp->key.i));
	  printf("%d\n",e);
	  /*
	  for(i = n-1; i >= 0; i--)
	    for(j = 0; j < i; j++)
	      if(adjacent(new,id[i],id[j]))
		{
		  printf("%d %d %d\n",id[j],id[i],getEdgeValue(new,id[i],id[j]));
		}
	  */
	  for(i = 0; i < n; i++)
	    {
	      for(j = i+1; j < n; j++)
		if(adjacent(new,id[i],id[j]))
		  {
		    printf("%d %d %d\n",id[i],id[j],getEdgeValue(new,id[i],id[j]));
		  }
	    }
  
	}
    
    }
  return 0;
}

int doc_dothi(Graph g, char* file_name)
{
  FILE *f = fopen(file_name,"r");
  if(!f)
    return 0;

  int n,m,i;
  fscanf(f,"%d",&n);
  int id;
  char name[MAX];
  for(i = 0; i < n; i++)
    {
      fscanf(f,"%d %s\n",&id,name);
      addVertex(g,id,name);
      // printf("%d--%s\n",id,name);
    }
  fscanf(f,"%d\n",&m);
  int v1,v2,w;
  for(i = 0; i < m; i++)
    {
      fscanf(f,"%d %d %d\n",&v1,&v2,&w);
      addEdge(g,v1,v2,w);
      addEdge(g,v2,v1,w);
      //   printf("%d %d %d\n",v1,v2,w);
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
