#ifndef N8ASM_COMPILER
#define N8ASM_COMPILER

#include "n8asm_core.h"
#include "n8asm_isetfile.h"

/*
	Compiler directives
*/
class Directive
{
public:
	virtual bool ParseDirective(String asm_line) = 0;
};

class ORG_Directive
{
public:
	virtual bool ParseDirective(String asm_line);
};

/*
	Stores essentials parameters of compiler
*/
struct N8CompilerParameters
{
	unsigned int ProgramMemorySize;
	String ISETFile;

	N8CompilerParameters();
};

/*
	Singleton class which permits the compilation
	of ASM file through ISET file, and outputs
	an executable HEX file
*/
class N8Compiler
{
	N8CompilerParameters _parameters;
	InstructionSet _instruction_set;

	static N8Compiler * _instance;	
	N8Compiler();

public:
	static N8Compiler * Instance();

	void Compile(String asm_file, String hex_out_file, bool verbose=true);
};

#endif