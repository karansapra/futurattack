/*
 * Shader.h
 *
 *  Created on: 18 oct. 2009
 *      Author: clement
 */

#ifndef SHADER_H_
#define SHADER_H_

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <stdio.h>

#include "BaseObject.h"

class Shader: public BaseObject {
	GLuint _vertex_shader;
	GLuint _fragment_shader;
	GLuint _program;

public:
	Shader();

	bool CreateShader(const char * vertex_shader, const char * fragment_shader);
	void EnableShader();
	void DisableShader();

	virtual ~Shader();
};

#endif /* SHADER_H_ */
