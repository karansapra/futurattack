#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <math.h>
#include <time.h>

#include "IRenderable.h"
#include "BitmapTexture.h"

namespace CJEngine
{

class Forest : 
	public IRenderable
{
	float *_tree_size;
	float *_angle;
	float _w;
	float _h;
	int _qty;
	char * _billboard_filename;

	GLuint _list;
	GLuint _tree_texture[1];

	float * _posx;
	float * _posy;

	void _setup_tree();

public:
	Forest(float tree_size, float width, float height, int qty, const char * billboard_filename);
	virtual ~Forest(void);

	void DeleteTrees(int x, int y, int width, int height);

	virtual void Render(float time);
};

}