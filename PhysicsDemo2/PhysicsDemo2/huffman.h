#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "types.h"

struct HuffmanWord
{
	U8 byte;
	U32 count;
};

typedef HuffmanWord[0xFF]	 DataStatTable;

void compute_stats(U8* data, U32 size);

#endif
