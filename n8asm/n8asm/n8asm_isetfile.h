#ifndef N8ASM_ISETFILE
#define N8ASM_ISETFILE

#include "n8asm_core.h"

enum ParsingError {ERR_OK, ERR_PARSE_ERROR};

class Operand
{
public:
	virtual String ParseAsmOperand(String str) = 0;
};

class Register : public Operand
{
public:
	virtual String ParseAsmOperand(String str);
};

class Immediate : public Operand
{
public:
	virtual String ParseAsmOperand(String str);
};

class RAMMemory : public Operand
{
public:
	virtual String ParseAsmOperand(String str);
};

class CodeMemory : public Operand
{
public:
	virtual String ParseAsmOperand(String str);
};

class Instruction
{
	String _pattern;
	String _asm_op;
	Operand * _opA;
	Operand * _opB;

public:
	Instruction(String asm_op_name,String pattern,String opA, String opB);
	String ParseAsmInstruction(String asm_line);
};

typedef std::vector<Instruction> InstructionSet;

InstructionSet ISetFileLoad(String isetfile);

#endif