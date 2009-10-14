/*
 * TestFrame.h
 *
 *  Created on: 1 oct. 2009
 *      Author: clement
 *
 *  Classe pour tester le moteur.
 */

#ifndef TESTFRAME_H_
#define TESTFRAME_H_

#include <math.h>
#include "IViewable.h"
#include "IKeyboard.h"
#include "Engine.h"
#include "SunRasterTexture.h"
#include "BitmapTexture.h"
#include "OBJ3DObject.h"

class TestFrame: public IViewable, public IKeyboard, public IMouse {
	float _current_zoom;
	float _ycam;
	float _x,_y;
	BitmapTexture * _sraster;
	BitmapTexture * _ground;
	GLuint _textures[2];

	OBJ3DObject * _base_case;

public:
	TestFrame();
	virtual ~TestFrame();

	bool AnimationFinished();

	void PreRender();
	void Render();


	const char * ToString();
	void KeyPressed(char key);
	void ButtonPressed(unsigned char button, int x, int y);


};

#endif /* TESTFRAME_H_ */
