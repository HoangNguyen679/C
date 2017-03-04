#include "adjgraph.h"


Graph createGraph()
{
	return make_jrb();
}


int insertEdge(Graph g, Jval v1, Jval v2,
				int (*cmp)(Jval, Jval))
{
	Graph found;
	Jval j_adj_list;
	Jval j = new_jval_v(NULL);
	found = jrb_find_gen(g, v1, cmp);

	if(found == NULL){
		/* if not found
		 create a new adjacent list which v2 is added to
		 then insert the adjacent list to the tree
		 with the key is v1
		*/

		 // create a new adj_list
		JRB adj_list = make_jrb();
		jrb_insert_gen(adj_list, v2, j, cmp);
		j_adj_list = new_jval_v(adj_list);

		// add adjacent list to the tree
		jrb_insert_gen(g, v1, j_adj_list, cmp);

		return 0;

	}else{
		/*
		if found
		check if v2 is in the adj_list of v1
				if not, add v2 to adj_list of v1
				else return status code 1
		*/

		JRB adj_list = (JRB) jval_v(found->val);
		found = jrb_find_gen(adj_list, v2, cmp);
		if(found == NULL){
			jrb_insert_gen(adj_list, v2, j, cmp);
			return 0;
		}else return 1;
	}
}


int addEdge(Graph g, Jval v1, Jval v2,
			int (*cmp)(Jval, Jval))
{
	/* find key v1 in graph
	if found, add v2 to the adjacent list of v1
	if not, create key v1 and add v2 to v1
	similar to v2
	*/
	int error_code1 = 0; // returned if error_code != 0
	int error_code2 = 0;

	error_code1 = insertEdge(g, v1, v2, cmp);
	error_code2 = insertEdge(g, v2, v1, cmp);
	
	return error_code1 + error_code2;

}


int adjacent(Graph g, Jval v1, Jval v2,
				int (*cmp)(Jval, Jval))
{
	JRB found = jrb_find_gen(g, v1, cmp);

	if(found == NULL){
		return 0;
	}else{
		found = jrb_find_gen((JRB) jval_v(found->val), v2, cmp);
		if(found == NULL) return 0;
		else return 1;
	}

}


JRB getAdjVertices(Graph g, Jval v1,
							int (*cmp)(Jval, Jval))
{
	JRB tmp, found;
	found = jrb_find_gen(g, v1, cmp);

	if(found == NULL) return NULL;
	else return (JRB) jval_v(found->val);
}


int cmpInt(Jval a, Jval b)
{
	return jval_i(a) - jval_i(b);
}


int cmpStr(Jval s1, Jval s2)
{
	return strcmp(jval_s(s1), jval_s(s2));
}


int getAdjVerticesI(Graph g, Jval v, int* output,
						int (*cmp)(Jval, Jval))
{
	// find note v
	JRB found = jrb_find_gen(g, v, cmp);
	JRB adj_list;
	JRB tmp;
	int count = 0;

	if(found == NULL){
		printf("ERROR: Node %d does not exist\n", jval_i(v));
		return 0;
	}else{
		adj_list = (JRB) jval_v(found->val);
		jrb_traverse(tmp, adj_list){
			output[count] = jval_i(tmp->key);
			count++;
		}
		return count;
	}
}


int addEdgeI(Graph g, int v1, int v2)
{
	return addEdge(g, ji(v1), ji(v2), &cmpInt);
}


int adjacentI(Graph g, int v1, int v2)
{
	return adjacent(g, ji(v1), ji(v2), &cmpInt);
}