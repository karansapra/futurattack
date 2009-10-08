/*
 * I3DObject.h
 *
 *  Created on: 4 oct. 2009
 *      Author: clement
 */

#ifndef I3DOBJECT_H_
#define I3DOBJECT_H_

#include <stdio.h>
#include <GL/freeglut.h>
#include "IRenderable.h"

struct Vertex3f
{
	float x;
	float y;
	float z;
};

struct Vertex2f
{
	float u;
	float v;
};

struct Triangle
{
	int vertex_indices[3];
	int normal_indices[3];
	int uv_indices[3];
};

class I3DObject: public IRenderable {
protected:

public:
	I3DObject();
	virtual ~I3DObject();

	virtual bool Load(const char * filename)=0;
};

#endif /* I3DOBJECT_H_ */
