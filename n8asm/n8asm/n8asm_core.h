#ifndef N8ASM_CORE
#define N8ASM_CORE

#include <string>
#include <vector>

typedef std::string						String;
typedef std::vector<String>				StringList;

/*
	Split input string str into many strings
	that represents tokens, ie the groups
	of alphanum strings

	ex: MOV R0,  R1
	Tokens returned:
	MOV
	R0
	R1
*/
StringList string_tokenizer(String str);

String uint_to_str(unsigned int n, unsigned int dynamic=16);
unsigned int str32_to_bin(String str32);

#endif