/*
 * PerspectiveCam.cpp
 *
 *  Created on: 30 oct. 2009
 *      Author: Clement
 */

#include "PerspectiveCam.h"

namespace CJEngine {

	PerspectiveCam::PerspectiveCam(float fovy, float aspect, float znear, float zfar) {
		_fovy = fovy;
		_aspect = aspect;
		_znear = znear;
		_zfar = zfar;

		_up[1] = 1.0;

		_eye[2] = 1500.0;
	}

	PerspectiveCam::~PerspectiveCam() {
		
	}

	void PerspectiveCam::SetEyePosition(const Vector<3> & eye)
	{
		_eye = eye;
	}

	void PerspectiveCam::SetLookAtPosition(const Vector<3> & lookat)
	{
		_lookat = lookat;
	}

	void PerspectiveCam::Apply()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(_fovy,_aspect,_znear,_zfar);
		gluLookAt(_eye[0],_eye[1],_eye[2],_lookat[0],_lookat[1],_lookat[2],_up[0],_up[1],_up[2]);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}
