/*
 * Mesh.h
 *
 *  Created on: 8 oct. 2009
 *      Author: clement
 */

#ifndef MESH_H_
#define MESH_H_

//Pour utiliser OpenGL 1.5, etc...
#define GL_GLEXT_PROTOTYPES

#include <GL/freeglut.h>
#include <GL/glx.h>
#include <GL/glext.h>

#include "IRenderable.h"
#include "I3DObject.h"
#include "Constants.h"


#define VERTEX_DATA 		0
#define NORMAL_DATA	 		1
#define TEXTURE_DATA	 	2

class Mesh: public IRenderable {
	GLuint _vbo[3];
	bool _already_built;
	bool _normal;
	bool _vertex;
	bool _texcoord;
	int _n;
	char _mesh_name[MAX_MESH_NAME_LENGTH];

	Vertex3f * _vertex_list;
	Vertex3f * _normal_list;
	Vertex2f * _texcoord_list;

public:
	Mesh();
	Mesh(const char *name);
	virtual ~Mesh();

	void SetVertexList(Vertex3f * vertex_list, int n);
	void SetNormalList(Vertex3f * normal_list, int n);
	void SetTexCoordList(Vertex2f * texcoord_list, int n);
	void BuildUp();

	void Render();

	const char * ToString();
};

#endif /* MESH_H_ */
