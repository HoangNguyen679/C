#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(){
	FILE *f = fopen("data.txt", "r");
	char s1[100];
	char s2[100];
	while (!feof(f)) {
		fscanf(f, "%s\t", s1);
		fgets(s2, 100, f);
		printf("%s-%s\n",s1,s2);
	}


}

void SortList(SLList *list) {
	node *p, *q;
	int i,j;
	elementType el;
	for (p=list->root; p!=NULL; p = p->next) {
		for (q=p->next; q!=NULL; q = q->next) {
			i = p->element.score;
			j = q->element.score;
			if (i < j) {
				el = p->element;			//
				p->element = q->element;	// -> Swap
				q->element = el;			//
			}
		}
	}
}