#include <stdio.h>
#include <stdlib.h>

typedef long elementType;

#include "StackLinkList.h"

int main(int argc, char const *argv[]) {
	stackType *bin = NULL, // bin is a stack to store binary numbers
			  *hex = NULL; // hex is a stack to store hexa numbers
	int dec, dec2; // dec is number which is inputed from user
	char hexa[16] = "0123456789ABCDEF";

	printf("Input Dec: ");
	scanf("%d", &dec);
	dec2 = dec;

	// Binary converting
	while(dec != 0){
		Push(dec%2, &bin);
		dec /= 2;
	}
	printf("Bin: "); while(bin != NULL) printf("%d", Pop(&bin));
	printf("\n");

	// Hexa converting
	while(dec2 != 0){
		Push(hexa[dec2%16], &hex);
		dec2 /= 16;
	}
	printf("Hex: "); while(hex != NULL) printf("%c", Pop(&hex));
	printf("\n");

	return 0;
}