/*
 * GameBackground.h
 *
 *  Created on: 30 oct. 2009
 *      Author: Clement
 */

#ifndef GAMEBACKGROUND_H_
#define GAMEBACKGROUND_H_

#include "CJEngine.h"

using namespace CJEngine;

enum AnimType {SLERP,LERP};

class GameBackground: public IScene {
	Skybox * _sb;
	PerspectiveCam * _camera_fond;
	Engine * _engine_instance;

	void RenderCase(float size);

	Vector<3> lookat_target;
	Vector<3> eye_target;

	Vector<3> lookat;
	Vector<3> eye;

public:
	GameBackground();
	virtual ~GameBackground();

	virtual void Render(float time);
	virtual void PreRender();

	void Move(float x, float z);

};

#endif /* GAMEBACKGROUND_H_ */
