#include <stdio.h>
#include <stdlib.h>

#include "n8asm_compiler.h"

int main(int argc, char ** argv)
{
	printf("N8 Assembler - Clement JACOB - 2010\n");
	N8Compiler * compiler = N8Compiler::Instance();
	compiler->Compile("src.asm","src.hex");
	system("PAUSE");
}

