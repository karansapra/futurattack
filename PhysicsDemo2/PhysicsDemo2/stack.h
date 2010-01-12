#ifndef STACK_H
#define STACK_H

#include "types.h"

struct StackBlockHeader
{
	PTR last_zone_ptr;
};

#define STACK_SIZE			1024*1024*16
#define SBH_SIZE			sizeof(StackBlockHeader)


class StackAllocator
{
	U8 stack[STACK_SIZE];
	U32 used_size;

	/*
	Performs a size bytes memory copy from src to dest
	*/
	void mem_write(U8 *dest, U8* src, U32 size);

public:
	StackAllocator();

	/*
	Return a free zone from the stack
	*/
	U8 * Allocate(U32 size);
	void FreeLast();
};

#endif
