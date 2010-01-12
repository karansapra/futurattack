#include "stack.h"

StackAllocator::StackAllocator()
{
	used_size = 0;
	for (U32 i=0;i<STACK_SIZE;i++)
		stack[i]=0x00;
}

U8 * StackAllocator::Allocate(U32 size)
{
	static StackBlockHeader sbh;
	

	_ASSERT(!(STACK_SIZE-used_size<size+SBH_SIZE));
	_ASSERT(size!=0);
	
	//Last block ptr retained
	sbh.last_zone_ptr = &stack[used_size];
	
	used_size += size;
	mem_write(&stack[used_size],(U8*)&sbh,SBH_SIZE);
	used_size += SBH_SIZE;

	return sbh.last_zone_ptr;
}

void StackAllocator::FreeLast()
{
	static StackBlockHeader sbh;

	_ASSERT(used_size!=0);
	mem_write((U8*)&sbh,&stack[used_size-SBH_SIZE],SBH_SIZE);
	used_size = sbh.last_zone_ptr-stack;
}

void StackAllocator::mem_write(U8 *dest, U8* src, U32 size)
{
	static U32 i;
	_ASSERT(size!=0);
	for (i=0;i<size;i++)
		dest[i] = src[i];
}