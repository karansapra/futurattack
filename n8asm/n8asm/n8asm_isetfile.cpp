#include "n8asm_isetfile.h"

#include <iostream>
#include <fstream>

InstructionSet ISetFileLoad(String isetfile)
{
	InstructionSet iset;
	char line[512];
	StringList instructions_lines;

	std::ifstream isetfilestream(isetfile.c_str());
	if (!isetfilestream)
		return iset;

	while (!isetfilestream.eof())
	{
		isetfilestream.getline(line,512);
		instructions_lines.push_back(String(line));
	}
	isetfilestream.close();

	/*
		Si l'on a pas au minimum 3 lignes, ce n'est
		pas un fichier correctement formate
	*/
	if (instructions_lines.size()<3)
		return iset;

	/*
		Quelques tests supplémentaires pour s'assurer du format
		correct du fichier ISET
	*/
	if (instructions_lines[0] != String("#ISETFILE") || instructions_lines[1].c_str()[0]!='#')
		return iset;
	
	StringList tokens;
	for (StringList::iterator i=instructions_lines.begin()+2;i!=instructions_lines.end();i++)
	{
		//Comment line?
		if (i->c_str()[0]=='#')
			continue;

		tokens.clear();
		tokens = string_tokenizer(*i);

		if (tokens.size()!=11)
			continue;
		
		String ptrn = tokens[3] + tokens[4] + tokens[5] + tokens[6] +
					  tokens[7] + tokens[8] + tokens[9] + tokens[10];
		
		iset.push_back(Instruction(tokens[0],ptrn,tokens[1],tokens[2]));

		//std::cout << ptrn << std::endl;
	}

	return iset;
}

Instruction::Instruction(String asm_op_name, String pattern, String opA, String opB)
{
	_asm_op = asm_op_name;
	_pattern = pattern;
	switch (opA.c_str()[0])
	{
	case 'R':
		_opA = new Register();
		break;
	case 'I':
		_opA = new Immediate();
		break;
	case 'M':
		_opA = new RAMMemory();
		break;
	case 'C':
		_opA = new CodeMemory();
		break;
	default:
		_opA = 0;
		break;
	}
	switch (opB.c_str()[0])
	{
	case 'R':
		_opB = new Register();
		break;
	case 'I':
		_opB = new Immediate();
		break;
	case 'M':
		_opB = new RAMMemory();
		break;
	case 'C':
		_opB = new CodeMemory();
		break;
	default:
		_opB = 0;
		break;
	}

}

String Instruction::ParseAsmInstruction(String asm_line)
{
	String result;
	unsigned char op_needed = 0;
	
	if (_opB==0 && _opA!=0)
		op_needed = 1;
	else if (_opA!=0)
		op_needed = 2;

	StringList tokens = string_tokenizer(asm_line);
	
	if (tokens.size()!=op_needed+1)
		return result;
	
	if (tokens[0]!=_asm_op)
		return result;

	String A,B;
	int posa;
	int posb;
	switch (op_needed)
	{
	case 0:
		return _pattern;
	case 1:
		result = _pattern;
		
		A = _opA->ParseAsmOperand(tokens[1]);		

		if (A.size()==0)
			return String();

		posa = result.find_first_of('a');
		posb = result.find_last_of('a');

		for (int i=posa;i<=posb;i++)
			result[i] = A[i-posa];

		return result;

	case 2:
		
		result = _pattern;
		
		A = _opA->ParseAsmOperand(tokens[1]);		
		B = _opB->ParseAsmOperand(tokens[2]);

		if (A.size()==0 || B.size()==0)
			return String();

		posa = result.find_first_of('a');
		posb = result.find_last_of('a');

		for (int i=posa;i<=posb;i++)
			result[i] = A[i-posa];

		posa = result.find_first_of('b');
		posb = result.find_last_of('b');

		for (int i=posa;i<=posb;i++)
			result[i] = B[i-posa];

		return result;
	default:
		return result;
	}
}

String Immediate::ParseAsmOperand(String str)
{
	String result;
	bool correct_format = true;
	bool hexformat = false;
	int pos = 0;
	for (String::iterator i=str.begin();i!=str.end();i++)
	{
		if (pos==1 && *i=='x')
			hexformat = true;
		else if (!(isdigit(*i)||(*i>='A'&&*i<='F')))
			correct_format = false;

		pos++;
	}

	if (!correct_format)
		return String();

	unsigned int i;

	if (hexformat)
		sscanf(str.c_str(),"%x",&i);
	else
		sscanf(str.c_str(),"%u",&i);

	result = uint_to_str(i,8);

	return result;
}

String Register::ParseAsmOperand(String str)
{
	String result;

	if (str.c_str()[0]!='R' || str.size()!=2)
		return result;

	unsigned int i = str.c_str()[1]-'0';
	
	switch (i)
	{
	case 0:
		return String("00");
	case 1:
		return String("01");
	case 2:
		return String("10");
	case 3:
		return String("11");
	default:
		return result;
	}
}

String RAMMemory::ParseAsmOperand(String str)
{
	String result;
	String adr;

	if (!(*str.begin()=='[' && *str.rbegin()==']'))
		return String();

	adr = str.substr(1,str.size()-2);

	bool correct_format = true;
	bool hexformat = false;
	int pos = 0;
	for (String::iterator i=adr.begin();i!=adr.end();i++)
	{
		if (pos==1 && *i=='x')
			hexformat = true;
		else if (!(isdigit(*i)||(*i>='A'&&*i<='F')))
			correct_format = false;

		pos++;
	}

	if (!correct_format)
		return String();

	unsigned int i;

	if (hexformat)
		sscanf(adr.c_str(),"%x",&i);
	else
		sscanf(adr.c_str(),"%u",&i);

	result = uint_to_str(i,16);

	return result;
}

String CodeMemory::ParseAsmOperand(String str)
{
	String result;
	bool correct_format = true;
	bool hexformat = false;
	int pos = 0;
	for (String::iterator i=str.begin();i!=str.end();i++)
	{
		if (pos==1 && *i=='x')
			hexformat = true;
		else if (!(isdigit(*i)||(*i>='A'&&*i<='F')))
			correct_format = false;

		pos++;
	}

	if (!correct_format)
		return String();

	unsigned int i;

	if (hexformat)
		sscanf(str.c_str(),"%x",&i);
	else
		sscanf(str.c_str(),"%u",&i);

	result = uint_to_str(i,12);

	return result;
}

