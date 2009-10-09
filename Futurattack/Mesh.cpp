/*
 * Mesh.cpp
 *
 *  Created on: 8 oct. 2009
 *      Author: clement
 */

#include "Mesh.h"

Mesh::Mesh() {
	// TODO Auto-generated constructor stub
	_vertex=false;
	_normal=false;
	_texcoord=false;
	_already_built=false;
	_n=-1;
}

Mesh::~Mesh() {
	// TODO Auto-generated destructor stub
}

void Mesh::SetVertexList(Vertex3f *vertex_list, int n)
{
	if (_already_built || (n!=_n && _n!=-1) || _vertex)
		return;
	printf("Vertices added\n");
	_n = n;
	_vertex = true;
	_vertex_list = new Vertex3f[n];
	memcpy(_vertex_list,vertex_list,n*sizeof(Vertex3f));
}

void Mesh::SetNormalList(Vertex3f *normal_list, int n)
{
	if (_already_built || (n!=_n && _n!=-1) || _normal)
		return;

	printf("Normals added\n");
	_n = n;
	_normal = true;
	_normal_list = new Vertex3f[n];
	memcpy(_normal_list,normal_list,n*sizeof(Vertex3f));
}

void Mesh::SetTexCoordList(Vertex2f *texcoord_list, int n)
{
	if (_already_built || (n!=_n && _n!=-1) || _texcoord)
		return;

	printf("Texcoords added\n");
	_n = n;
	_texcoord = true;
	_texcoord_list = new Vertex2f[n];
	memcpy(_texcoord_list,texcoord_list,n*sizeof(Vertex2f));
}

const char *Mesh::ToString()
{
	return "Mesh";
}



void Mesh::Render()
{
	if (!_already_built || !_vertex)
		return;

	if (_vertex)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER,_vbo[VERTEX_DATA]);
		glVertexPointer(3,GL_FLOAT,0,0);
	}

	if (_normal)
	{
		glEnableClientState(GL_NORMAL_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER,_vbo[NORMAL_DATA]);
		glNormalPointer(GL_FLOAT,0,0);
	}

	if (_texcoord)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER,_vbo[TEXTURE_DATA]);
		glTexCoordPointer(2,GL_FLOAT,0,0);
	}
	glDrawArrays(GL_TRIANGLES,0,_n);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Mesh::BuildUp()
{
	glGenBuffers(3,_vbo);

	if (_vertex)
	{
		glBindBuffer(GL_ARRAY_BUFFER,_vbo[VERTEX_DATA]);
		glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex3f)*_n,_vertex_list,GL_STATIC_DRAW);
		delete[] _vertex_list;
	}
	if (_normal)
	{
		glBindBuffer(GL_ARRAY_BUFFER,_vbo[NORMAL_DATA]);
		glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex3f)*_n,_normal_list,GL_STATIC_DRAW);
		delete[] _normal_list;
	}
	if (_texcoord)
	{
		glBindBuffer(GL_ARRAY_BUFFER,_vbo[TEXTURE_DATA]);
		glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex2f)*_n,_texcoord_list,GL_STATIC_DRAW);
		delete[] _texcoord_list;
	}

	_already_built=true;
}


