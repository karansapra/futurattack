/*
 * Camera.cpp
 *
 *  Created on: 1 oct. 2009
 *      Author: clement
 */

#include "Camera.h"

Camera::Camera() {
	// TODO Auto-generated constructor stub
	_eyex = 0.0;
	_eyey = 100.0;
	_eyez = 100.0;

	_posx = 0.0;
	_posy = 0.0;
	_posz = 0.0;

	_z = 1.0;

	_mx = 0.0;
	_my = 0.0;
	_mz = 0.0;

	_params_changed = true;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::SetEyePosition(float eyex, float eyey, float eyez)
{
	_params_changed = true;
	_eyex = eyex;
	_eyey = eyey;
	_eyez = eyez;
}

void Camera::ApplyChanges()
{
	_params_changed = false;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(_mx,_my,_mz);
	glScalef(_z,_z,_z);
	glOrtho(_left,_right,_bottom,_top,_near,_far);
	gluLookAt(_eyex,_eyey,_eyez,_posx,_posy,_posz,0.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Camera::SetLookAtPosition(float posx, float posy, float posz)
{
	_params_changed = true;
	_posx = posx;
	_posy = posy;
	_posz = posz;
}

void Camera::SetVolumeView(float left, float right, float top, float bottom, float near, float far)
{
	_params_changed = true;
	_left = left;
	_right = right;
	_top = top;
	_bottom = bottom;
	_near = near;
	_far = far;
}

bool Camera::HasChanged()
{
	return _params_changed;
}

void Camera::Zoom(float z)
{
	_params_changed = true;
	_z = z;
}

void Camera::Move(float x, float y, float z)
{
	_params_changed = true;

	_mx = x;
	_my = y;
	_mz = z;
}

const char *Camera::ToString()
{
	return "Camera";
}


