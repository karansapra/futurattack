/*
 * TestFrame.h
 *
 *  Created on: 1 oct. 2009
 *      Author: clement
 */

#ifndef TESTFRAME_H_
#define TESTFRAME_H_

#include <math.h>
#include "IViewable.h"
#include "IKeyboard.h"
#include "Engine.h"

class TestFrame: public IViewable, public IKeyboard, public IMouse {
	float _current_zoom;
	float _ycam;
	float _x,_y;

public:
	TestFrame();
	virtual ~TestFrame();

	void PreRender();
	void Render();
	const char * ToString();
	void KeyPressed(char key);
	void ButtonPressed(unsigned char button, int x, int y);
};

#endif /* TESTFRAME_H_ */
