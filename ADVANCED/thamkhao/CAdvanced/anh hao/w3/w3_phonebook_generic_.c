#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define ARRSIZE 	10
#define RANGE 		26
#define EPSILON 	1E-7
#define MAX_BUFF 	512

#define INITIAL_SIZE 		10
#define INCREMENTAL_SIZE 	5
#define BUFF_SIZE			80

#define NEWLINE 	printf("%s", "\n");

typedef struct 
{
	void  		*key;
	void 		*value;
} Entry;

typedef struct
{
	Entry 		*entries;
	int 		total;
	int 		size;
	Entry 		(*MakeNode)(void*, void*);
	int 		(*Compare)(void*, void*);
} SymbolTable;

// SymbolTable API
SymbolTable CreateSymbolTable(int size, Entry (*MakeNode)(void*, void*), int (*Compare)(void*, void*));
void DropSymbolTable(SymbolTable *st);
void AddEntry(void* key, void* value, SymbolTable *st);
Entry GetEntry(void *key, SymbolTable st);
int BinarySearchEntry(SymbolTable st, int l, int r, void *key, int(*compare_func)(void*, void*), int *found);
int _compare_func(void* a, void *b);

// PhoneBook's function
Entry MakePhoneEntry(void *name, void *number);
int ComparePhoneEntry(void *name1, void*name2);


//----------------------------------------------------------------------------
typedef SymbolTable PhoneBook;


int main(int argc, char const *argv[])
{
	PhoneBook myPhoneBook = CreateSymbolTable(INITIAL_SIZE, MakePhoneEntry, ComparePhoneEntry);

	unsigned long tmpNumber = 1663872498;
	AddEntry("Hao", &tmpNumber, &myPhoneBook);
	
	tmpNumber = 345678456;
	AddEntry("Dung", &tmpNumber, &myPhoneBook);

	tmpNumber = 169246141;
	AddEntry("Huong", &tmpNumber, &myPhoneBook);

	Entry re = GetEntry("Huong", myPhoneBook);
	if (re.value != NULL)
	{
		printf("%s: %ld\n", re.key, *(long*)(re.value));
	}
	
	DropSymbolTable(&myPhoneBook);
	return 0;
}


//----------------------------------------------------------------------------
SymbolTable CreateSymbolTable(int size, Entry (*MakeNode)(void*, void*), int (*Compare)(void*, void*))
{
	SymbolTable st;
	st.entries = (Entry*)malloc(sizeof(Entry)*size);
	st.size = size;
	st.total = 0;
	st.MakeNode = MakeNode;
	st.Compare = Compare;
	return st;
}
//----------------------------------------------------------------------------
void DropSymbolTable(SymbolTable *st)
{
	st->size = 0;
	st->total = 0;
	free(st->entries);
	st->entries = NULL;
	st->MakeNode = NULL;
	st->Compare = NULL;
}
//----------------------------------------------------------------------------
void AddEntry(void* key, void* value, SymbolTable *st)
{
	if (st->total >= st->size)
	{
		SymbolTable newst = CreateSymbolTable(st->size + INCREMENTAL_SIZE, st->MakeNode, st->Compare);
		newst.size = st->size + INCREMENTAL_SIZE;
		newst.total = st->total;
		memcpy(newst.entries, st->entries, sizeof(SymbolTable)*st->total);
		DropSymbolTable(st);
		*st = newst;
	}

	if (st->total == 0)
	{
		st->entries[0] = st->MakeNode(key, value);
		st->total = 1;
		return;
	}

	int found;
	int pos = BinarySearchEntry(*st, 0, st->total-1, key, st->Compare, &found);
	
	// If there already exists an entry, just update it.
	if (found == 1)	
		st->entries[pos].value = value;
	else // insert new entry to ST
	{
		st->total++;
		// move data for one element then insert to this position
		SymbolTable *temp = (SymbolTable*)malloc(sizeof(SymbolTable)*st->total);
		memcpy(temp, (st->entries)+pos, sizeof(SymbolTable)*(st->total-1-pos));
		st->entries[pos] = st->MakeNode(key, value);
		memcpy((st->entries)+pos+1, temp, sizeof(SymbolTable)*(st->total-1-pos));
		free(temp); temp = NULL;
	}
}
//----------------------------------------------------------------------------
Entry GetEntry(void *key, SymbolTable st)
{
	int found;
	int pos = BinarySearchEntry(st, 0, st.total, key, st.Compare, &found);
	if (found == 1)	
		return st.entries[pos];
	else
	{
		Entry _null;
		_null.key = NULL;
		_null.value = NULL;
		return _null;	
	}
}
//----------------------------------------------------------------------------
int BinarySearchEntry(SymbolTable st, int l, int r, void *key, int(*compare_func)(void*, void*), int *found)
{
	if (l > r) {*found = 0; return l;}
	int m = (l + r) / 2;
	if (compare_func(st.entries[m].key, key) > 0) return BinarySearchEntry(st, l, m - 1, key, compare_func, found);
	if (compare_func(st.entries[m].key, key) < 0) return BinarySearchEntry(st, m + 1, r, key, compare_func, found);
	if (compare_func(st.entries[m].key, key) == 0) { *found = 1; return m; }
}
//----------------------------------------------------------------------------
int _compare_func(void* a, void *b)
{
	// This is sample function
	// if (a > b) return 1;
	// if (a < b) return -1;
	// if (a == b)
	return 0;
}



//----------------------------------------------------------------------------
Entry MakePhoneEntry(void *name, void *number)
{
	Entry newPhone;
	newPhone.key = strdup((char*)name);
	// What is strdup???
	// char *strdup (const char *s) {
	//     char *d = malloc (strlen (s) + 1);   // Space for length plus nul
	//     if (d == NULL)
	//         return NULL;                     // No memory
	//     strcpy (d,s);                        // Copy the characters
	//     return d;                            // Return the new string
	// }
	// newPhone.value = malloc(sizeof(long));
	// newPhone.value = (long*)number;
	newPhone.value = malloc(sizeof(long));
	memcpy(newPhone.value, number, sizeof(long));
	return newPhone;
}
//----------------------------------------------------------------------------
int ComparePhoneEntry(void *name1, void*name2)
{
	return strcmp((char*)name1, (char*)name2);
}