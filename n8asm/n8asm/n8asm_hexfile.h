#ifndef N8ASM_HEXFILE
#define N8ASM_HEXFILE

#include "n8asm_core.h"

class N8HexFile
{
	unsigned char * _data;
	unsigned int _current_position, _reserved_size;
	
public:
	N8HexFile(unsigned int kbsize);
	~N8HexFile();

	void Goto(unsigned int adr);
	void Write(unsigned char byte);
	void Write(unsigned int word);
	void SaveAsHex(String file);
	void Clear();
};

#endif