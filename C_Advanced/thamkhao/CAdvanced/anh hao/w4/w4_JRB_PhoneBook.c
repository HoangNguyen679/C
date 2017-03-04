#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "jrb.h"

#define ARRSIZE 	10
#define RANGE 		26
#define EPSILON 	1E-7
#define MAX_BUFF 	512

#define NEWLINE 	printf("%s", "\n");

int main(int argc, char const *argv[])
{
	JRB node;
	JRB phoneBook = make_jrb(); 

	jrb_insert_str(phoneBook, "Hao", new_jval_l(1663872498));


	jrb_traverse(node, phoneBook)
	{
		printf("%s: %ld\n", node->key, node->val);
	}

	return 0;
}