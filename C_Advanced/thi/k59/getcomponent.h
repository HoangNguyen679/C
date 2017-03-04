int BFS_C(Graph graph,int start,int count,int *visited)
{
  int n,output[100],i,u,v;
  Dllist node,queue;
  queue=new_dllist();
  dll_append(queue,new_jval_i(start));
  if(visited[start]!=count)
    count++; //khong hieu ????
  while(!dll_empty(queue))
    {
      node=dll_first(queue);
      u=jval_i(node->val);
      dll_delete_node(node);
      if(!visited[u])
        {
          visited[u]=count;
          n=outdegree(graph,u,output);
          for(i=0;i<n;i++)
            {
              v=output[i];
              if(!visited[v])
                dll_append(queue,new_jval_i(v));
            }
     	}
    }
  return count;
}
int getComponments(Graph graph,void (*func)(int *,int)){ // so nhanh cua do thi
  int *visited=(int*)malloc(1000*sizeof(int));
  JRB node;
  int count=1;
  jrb_traverse(node,graph.edges)
    visited[jval_i(node->key)]=0;
  jrb_traverse(node,graph.edges)
    count=BFS_C(graph,jval_i(node->key),count,visited);
  jrb_traverse(node,graph.vertices)
    if(!visited[jval_i(node->key)])
      count++;
  func(visited,count);
  return count-1;
}
