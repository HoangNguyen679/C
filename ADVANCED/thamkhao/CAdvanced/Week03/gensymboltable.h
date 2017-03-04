#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct Entry {
	void* key;
	void* value;
} Entry;

typedef struct SymbolTable
{
	Entry* entries;
	int size;
	int total;
	Entry* (*makeNewEntry)(void*, void*);
	int (*cmpFunction)(void*, void*);
} SymbolTable;

SymbolTable* creatSymbolTable(
    Entry * (*makeNewEntry)(void*, void*),
    int(*cmpFunction)(void*, void*))
{
	SymbolTable* s_table = (SymbolTable*)malloc(sizeof(SymbolTable));
	s_table->size = INITIAL_SIZE;
	s_table->entries = (Entry*)malloc(sizeof(Entry) * s_table->size);
	s_table->total = 0;
	s_table->makeNewEntry = makeNewEntry;
	s_table->cmpFunction = cmpFunction;

	return s_table;
}

void dropSymbolTable(SymbolTable* s_table) {
	free(s_table->entries);
	s_table->total = 0;
	s_table->size = 0;
	free(s_table);
}

void addEntry(void* key, void* value, SymbolTable* s_table) {
	s_table->total++;
	if (s_table->total > s_table->size) {// if exceed maximum size
		s_table->size += INCREMENTAL_SIZE;
		s_table->entries = (Entry*)realloc(s_table->entries, sizeof(Entry) * s_table->size);
	}

	s_table->entries[s_table->total - 1] = *s_table->makeNewEntry(key, value);
}

int searchEntry(void* key, SymbolTable* s_table) {
	int i;
	for (i = 0; i < s_table->total; i++) {
		if (s_table->cmpFunction(key, s_table->entries[i].key) == 0)
			return i;
	}
	return -1;
}

Entry* getEntry(void* key, SymbolTable* s_table) {
	int i;
	for (i = 0; i < s_table->total; i++) {
		if (s_table->cmpFunction(key, s_table->entries[i].key) == 0)
			return &s_table->entries[i];
	}
	return NULL;
}