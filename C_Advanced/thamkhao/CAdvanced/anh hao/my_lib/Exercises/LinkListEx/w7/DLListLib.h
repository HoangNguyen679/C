typedef struct My_Node{
	struct My_Node *prev;
	elementType element;
	struct My_Node *next;
} node;

node *head = NULL;
node *tail = NULL;
node *cur = NULL;

void clrBuff(void);
void ImportFile(FILE *fileIn);
node *MakeNewNode(elementType e);
void InsertAfterCurrent(elementType e);
void InsertBeforeCurrent(elementType e);
void InsertAtPosition(elementType e, int position);
void DeleteAtPosition(int position);
void DeleteCurrent(void);
node *MoveCurToPosition(int position);
void PrintData(elementType e);
void TraverseList(void);
void TraverseRevertList(void);
void FreeAllList();


void clrBuff(){
	while(getchar()!='\n');
}

elementType ReadFile(FILE *fileIn){
	elementType temp;
	int irc;
	irc = fread(&temp, sizeof(elementType), 1, fileIn);
	if (irc == 0) return;
	return temp;
}

void ImportFile(FILE *fileIn){
	//This will Insert node from dat file (Insert after Current)
	elementType temp;
	int irc;
	while(1){
		irc = fread(&temp, sizeof(elementType), 1, fileIn);
		if (irc == 0) break;
		InsertAfterCurrent(temp);
	}
	fclose(fileIn);
}

node *MakeNewNode(elementType e){
	node *new = (node*)malloc(sizeof(node));
	new->prev = NULL;
	new->next = NULL;
	new->element = e;
	return new;
}

void TraverseList(){
	node *p;
	if(head == NULL){
		printf("List is Empty!\n");
		return;
	}
	for(p = head; p != NULL; p = p->next){
		PrintData(p->element);
	}
}

void TraverseRevertList(){
	node *p;
	if(head == NULL){
		printf("List is Empty!\n");
		return;
	}
	for(p = tail; p != NULL; p = p->prev){
		PrintData(p->element);
	}
}


void InsertAfterCurrent(elementType e){
	node *new = MakeNewNode(e);
	if(head == NULL){
		head = new;
		tail = new;
		cur = new;
	}
	else if(cur == tail){
		new->prev = cur;
		new->next = NULL;

		cur->next = new;
		tail = new;
		cur = tail;
	}
	else{
		new->prev = cur;
		new->next = cur->next;

		cur->next->prev = new;
		cur->next = new;

		//current must be new
		cur = new;
	}
}

void InsertBeforeCurrent(elementType e){
	node *new = MakeNewNode(e);
	if(head == NULL){
		head = new;
		tail = new;
		cur = new;
	}
	else if(cur->prev == NULL){
		new->prev = NULL;
		new->next = cur;

		cur->prev = new;
		head = new;
		cur = new;
	}
	else{
		new->prev = cur->prev;
		new->next = cur;

		cur->prev->next = new;
		cur->prev = new;

		//current must be new
		cur = new;
	}
}

node *MoveCurToPosition(int position){
	cur = head;
	int i;
	for(i = 0; i < position; i++){
		if (cur->next == tail->next){
		}
		else cur = cur->next;
	}
	return cur;
}

void InsertAtPosition(elementType e, int position){
	cur = head;
	if(position == 0) InsertBeforeCurrent(e);
	else{
		int i;
		for(i = 1; i < position; i++){
			if (cur->next == NULL){
			}
			else cur = cur->next;
		}
		InsertAfterCurrent(e);
	}
}

void DeleteCurrent(void){
	if (cur == head){
		head->next->prev = NULL;
		head = head->next;
		free(cur);
		cur = head;
	}
	else if (cur == tail){
		tail->prev->next = NULL;
		tail = tail->prev;
		free(cur);
		cur = tail;
	}
	else{
		node *toDel = cur;
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		cur = cur->prev;
		free(toDel);
	}
}

void DeleteAtPosition(int position){
	cur = MoveCurToPosition(position);
	DeleteCurrent();
}

void FreeAllList(){
	node *toFree = head;
	while(toFree != NULL) {
		head = head->next;
		free(toFree);
		toFree = head;
	}
}
