/*
 * Shader.cpp
 *
 *  Created on: 18 oct. 2009
 *      Author: clement
 */

#include "Shader.h"

Shader::Shader() {
	_vertex_shader = 0;
	_fragment_shader = 0;
}

bool Shader::CreateShader(const char *vertex_shader, const char *fragment_shader)
{
	_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	if (_fragment_shader==0 || _vertex_shader==0)
		return false;

	char vertex_string[80*400]; //400 Lignes max!
	char fragment_string[80*400]; //400 Lignes max!

	FILE * f_vertex_shader = fopen(vertex_shader,"r");
	if (f_vertex_shader==NULL)
		return false;

	FILE * f_fragment_shader = fopen(fragment_shader,"r");
	if (f_fragment_shader==NULL)
	{
		fclose(f_vertex_shader);
		return false;
	}

	int pos = 0;
	while (!feof(f_vertex_shader))
		vertex_string[pos++] = fgetc(f_vertex_shader);
	vertex_string[pos-1] = 0x00;

	pos = 0;
	while (!feof(f_fragment_shader))
		fragment_string[pos++] = fgetc(f_fragment_shader);
	fragment_string[pos-1] = 0x00;

	GLchar * StringPointer[1];

	/*
	 * On injecte le code dans la CG pour compilation
	 */
	StringPointer[0] = vertex_string;
	glShaderSource(_vertex_shader,1,(const GLchar ** )StringPointer,NULL);
	StringPointer[0] = fragment_string;
	glShaderSource(_fragment_shader,1,(const GLchar ** )StringPointer,NULL);


	/*
	 * Compilation
	 */
	int success;

	glCompileShader(_vertex_shader);
	glGetShaderiv(_vertex_shader,GL_COMPILE_STATUS,&success);
	if (!success)
	{
		GLchar infoLog[4096];
		glGetShaderInfoLog(_vertex_shader,4096,NULL,infoLog);
		printf("Compilation error while compiling vertex shader\n");
		printf("%s\n",infoLog);
		return false;
	}


	glCompileShader(_fragment_shader);
	glGetShaderiv(_fragment_shader,GL_COMPILE_STATUS,&success);
	if (!success)
	{
		GLchar infoLog[4096];
		glGetShaderInfoLog(_fragment_shader,4096,NULL,infoLog);
		printf("Compilation error while compiling fragment shader\n");
		printf("%s\n",infoLog);
		return false;
	}

	_program = glCreateProgram();

	glAttachShader(_program,_vertex_shader);
	glAttachShader(_program,_fragment_shader);

	glLinkProgram(_program);
	glGetProgramiv(_program,GL_LINK_STATUS,&success);
	if (!success)
	{
		GLchar infoLog[4096];
		glGetProgramInfoLog(_program,4096,NULL,infoLog);
		printf("Compilation error while linking shader\n");
		printf("%s\n",infoLog);
		return false;
	}

	return true;
}

void Shader::EnableShader()
{
	glUseProgram(_program);
}

void Shader::DisableShader()
{
	glUseProgram(0);
}

Shader::~Shader() {
	if (_vertex_shader!=0)
		glDeleteShader(_vertex_shader);
	if (_fragment_shader!=0)
		glDeleteShader(_fragment_shader);
	glDeleteProgram(_program);
}
