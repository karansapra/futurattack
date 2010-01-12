#include "huffman.h"

void compute_stats(U8* data, U32 size)
{
	static U32 stat_table[0xFF];
	static U32 i;

	/*
	Zero fill
	*/
	for (i=0;i<0xFF;i++)
		stat_table[i] = 0x00000000;

	/*
	Stat creation
	*/
	for (i=0;i<size;i++)
		stat_table[data[i]]++;
	

}