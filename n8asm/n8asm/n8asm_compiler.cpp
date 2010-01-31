#include "n8asm_compiler.h"
#include "n8asm_hexfile.h"
#include <iostream>
#include <fstream>

N8CompilerParameters::N8CompilerParameters()
{
	ProgramMemorySize = 16*1024; //16kB program ROM size
	ISETFile = String("./n8set.iset");
}

N8Compiler::N8Compiler()
{
	_instruction_set = ISetFileLoad(_parameters.ISETFile);
}

N8Compiler * N8Compiler::_instance = 0;

N8Compiler * N8Compiler::Instance()
{
	if (_instance==0)
		_instance = new N8Compiler();

	return _instance;
}

void N8Compiler::Compile(String asm_file, String hex_out_file, bool verbose)
{
	StringList asm_file_lines;
	N8HexFile hex_file(_parameters.ProgramMemorySize);

	char line[512];
	std::ifstream asmfilestream(asm_file.c_str());
	if (!asmfilestream)
	{
		if (verbose)
			std::cout << "ASM Sourcefile not found" << std::endl;
		return;
	}

	while (!asmfilestream.eof())
	{
		asmfilestream.getline(line,512);
		asm_file_lines.push_back(String(line));
	}
	asmfilestream.close();	

	InstructionSet::iterator iseti;
	unsigned int line_ctr = 0;
	bool compilation_successful = true;

	for (StringList::iterator i=asm_file_lines.begin();i!=asm_file_lines.end();i++)
	{
		line_ctr++;
		//Not enough chars or a comment, dont parse
		if (i->size()<3 || i->c_str()[0]=='#')
			continue;

		bool no_err = false;

		if (*i->begin()=='[')
		{
			//Directive case
			StringList dir_tokens = string_tokenizer(*i);
			if (dir_tokens[0]==String("[ORG]") && dir_tokens.size()==2)
			{
				String str=dir_tokens[1];
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
				
				if (correct_format)
				{
					unsigned int i;
					if (hexformat)
						sscanf(str.c_str(),"%x",&i);
					else
						sscanf(str.c_str(),"%u",&i);				
					hex_file.Goto(i);
				}

				no_err = true;
				continue;
			}				
			
		} else
		{
			//Instruction case
			for (iseti=_instruction_set.begin();iseti!=_instruction_set.end();iseti++)
			{
				String binarycode = iseti->ParseAsmInstruction(*i);
				if (binarycode.size()!=0)
				{	
					compilation_successful = true;
					no_err=true;
					try
					{
						hex_file.Write(str32_to_bin(binarycode));
					} catch (std::exception e)
					{
						std::cout << e.what() << std::endl;
						no_err = false;
						compilation_successful = false;
					}				
					break;
				} else
					compilation_successful = false;
			}
		}
		if (!no_err && verbose)
		{
			std::cout << "Error at line " << line_ctr << std::endl;
			std::cout << "     -> " << *i << std::endl;
		}
	}

	if (compilation_successful)
	{
		std::cout << "Writing HEX..." << std::endl;
		hex_file.SaveAsHex(hex_out_file);
		std::cout << "Compilation successful" << std::endl;
	}

}