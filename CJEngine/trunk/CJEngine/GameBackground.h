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

class GameBackground: public IScene {
	Skybox * _sb;
	PerspectiveCam * _camera_fond;
	PerspectiveCam * _lamp_camera;
	Engine * _engine_instance;

	int _data_grid[11*11];

	void RenderCase(float size);

	Forest *_forest;

	Vector<3> lookat_target;
	Vector<3> eye_target;

	Vector<3> lamp_lookat;
	Vector<3> lamp_position;

	GLuint _arbre[1];

	GLuint _ground_texture[1];
	GLuint _depth_text[1];

	Vector<3> lookat;
	Vector<3> eye;

	bool _select;

public:
	GameBackground();
	virtual ~GameBackground();

	virtual void Render(float time);
	virtual void PreRender();

	void Move(float x, float z);
	void SelectionMode(int x, int y);
	bool switch_cam;
	bool take_photo;
};

#endif /* GAMEBACKGROUND_H_ */
