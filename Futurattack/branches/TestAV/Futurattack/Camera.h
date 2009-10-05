/*
 * Camera.h
 *
 *  Created on: 1 oct. 2009
 *      Author: clement
 *
 *
 * Classe de gestion de la camera orthogonale
 *
 * On peut fixer la position de la camera, son point de visée, le volume
 * de vision.
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <GL/freeglut.h>
#include "BaseObject.h"

class Camera: public BaseObject {

protected:
	float _eyex, _eyey, _eyez;
	float _posx, _posy, _posz;
	float _left, _right, _top, _bottom, _near, _far;
	float _mx, _my, _mz;
	float _z;
	bool _params_changed;


public:
	Camera();
	virtual ~Camera();

	void SetVolumeView(float left, float right, float top, float bottom, float near, float far);
	void SetEyePosition(float eyex, float eyey, float eyez);
	void SetLookAtPosition(float posx, float posy, float posz);
	void Zoom(float z);
	void Move(float x, float y, float z);
	void ApplyChanges();
	bool HasChanged();

	const char * ToString();
};

#endif /* CAMERA_H_ */
