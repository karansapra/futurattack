#include "./FX.h"
#include "./Core.h"

bool loadfile(const char * filename, char * buffer, int size)
{
	ZeroMemory(buffer,size);
	FILE * f;
	
	if (fopen_s(&f,filename,"r")!=0)
		return false;
	
	fread_s(buffer,size,1,size,f);
	fclose(f);
	return true;
}

FX::FX(const char * vert_fx, const char * frag_fx)
{
	frag_ = false;
	vert_ = false;

	//Fragment shader loading
	if (frag_fx!=0)
	{
		char frag_src[2048];		
		loadfile(frag_fx,frag_src,2048);
		char * lines[1];
		lines[0] = frag_src;
		printf("FRAG SHADER:\n%s\n\n",frag_src);
		frag_shader_ = glCreateShader(GL_FRAGMENT_SHADER);		
		glShaderSource(frag_shader_,1,(const GLchar**)lines,NULL);
		glCompileShader(frag_shader_);
		GLint status;
		glGetShaderiv(frag_shader_,GL_COMPILE_STATUS,&status);
		if (!status)
			printf("Error while compiling fragment shader\n");
		else
			frag_ = true;
	}

	//Vertex shader loading
	if (vert_fx!=0)
	{
		char vert_src[2048];
		loadfile(vert_fx,vert_src,2048);
		char * lines[1];
		lines[0] = vert_src;
		printf("VERT SHADER:\n%s\n\n",vert_src);
		vert_shader_ = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vert_shader_,1,(const GLchar**)lines,NULL);
		glCompileShader(vert_shader_);
		GLint status;
		glGetShaderiv(vert_shader_,GL_COMPILE_STATUS,&status);
		if (!status)
			printf("Error while compiling vertex shader\n");
		else
			vert_ = true;
	}	
	
	 shader_prog_ = glCreateProgram();
	 
	 if (frag_)
		 glAttachShader(shader_prog_,frag_shader_);
	 if (vert_)
		 glAttachShader(shader_prog_,vert_shader_);

	 glLinkProgram(shader_prog_);
	 glValidateProgram(shader_prog_);
}

FX::~FX(void)
{
	glDeleteShader(frag_shader_);
	glDeleteShader(vert_shader_);
}

void FX::Enable()
{
	glUseProgram(shader_prog_);
}

void FX::Disable()
{
	glUseProgram(0);
}