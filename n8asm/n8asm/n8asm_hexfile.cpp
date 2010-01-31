#include "n8asm_hexfile.h"

#include <iostream>
#include <fstream>

N8HexFile::N8HexFile(unsigned int kbsize)
{
	_data = new unsigned char[kbsize];
	_current_position = 0;
	_reserved_size = kbsize;
	Clear();
}

N8HexFile::~N8HexFile()
{
	delete[] _data;
}

void N8HexFile::Goto(unsigned int adr)
{
	if (adr<_reserved_size)
		_current_position = adr;
	else
		throw std::exception("Outside memory");
}

void N8HexFile::Write(unsigned char byte)
{
	if (_current_position>=_reserved_size)
		throw std::exception("End of memory");
	_data[_current_position++] = byte;
}

void N8HexFile::Write(unsigned int word)
{
	unsigned char *adr = (unsigned char *)&word;
	if (_current_position+3>=_reserved_size)
		throw std::exception("End of memory");
	_data[_current_position++] = adr[0];
	_data[_current_position++] = adr[1];
	_data[_current_position++] = adr[2];
	_data[_current_position++] = adr[3];
}

void N8HexFile::SaveAsHex(String file)
{
	std::ofstream f(file.c_str());
	f.write((const char *)_data,_reserved_size);
	f.close();
}

void N8HexFile::Clear()
{
	for (unsigned int i=0;i<_reserved_size;i++)
		_data[i] = 0x00;
}
