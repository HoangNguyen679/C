#include "digraph.h"


typedef struct{
	Graph g;
	int root;
} HuffmanTree;

typedef struct{
	int size;
	int bits;
} Coding;

//Coding HuffmanTable[256];

/* build huffman tree from a string */
HuffmanTree makeHuffman(char* buffer, int size);
void createHuffmanTable(HuffmanTree htree, int root, Coding *htable, int level, int *bits);
int getBit(int bits, int offset);
void compress(char *buffer, int size, char *huffman, int *nbit);