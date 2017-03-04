typedef struct typeTree{
	elementType info[MAX];
	int size;
}typeTree;
// This function make the whole tree get value from their child if they don't
void initTree(typeTree *tree){
	tree->size = 0;
}
void addTree(typeTree *tree, elementType a){
	tree->size++;
	assignmentElementType(&tree->info[tree->size],a);
}
elementType *getvalue(typeTree *tree,int root, int * is_value(elementType)){
	if (is_value(tree->info[root])) return &tree->info[root];
	if (!is_value(tree->info[root*2])) getvalue(tree, root*2, is_value );
	if (!is_value(tree->info[root*2 + 1])) getvalue(tree, root*2 + 1, is_value );
	if (rand() % 2 == 0) 
		assignmentElementType(&tree->info[root], *getvalue(tree, root * 2, is_value));
	else 
		assignmentElementType( &tree->info[root], *getvalue(tree, 1 + root * 2 , is_value));
	return &tree->info[root];
}
void inOrderTraverse(typeTree *tree, int root, void *function_x(int)){
	if (root << 1 <= tree->size) inOrderTraverse(tree, root * 2, function_x);
	function_x(root);
	if (root << 1 < tree->size) inOrderTraverse(tree, 1 + root * 2, function_x);
}