/*
 * Skybox.h
 *
 *  Created on: 28 oct. 2009
 *      Author: Clement
 */

#ifndef SKYBOX_H_
#define SKYBOX_H_


#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "IRenderable.h"
#include "BitmapTexture.h"

namespace CJEngine {

class Skybox: public CJEngine::IRenderable {

	BitmapTexture * _faces[6];
	GLuint _textures_gl[1];

	float _skybox_size;

public:
	Skybox(const char * basename);
	virtual ~Skybox();

	void SetSize(float size);

	virtual void Render(float time);
};

}

#endif /* SKYBOX_H_ */
