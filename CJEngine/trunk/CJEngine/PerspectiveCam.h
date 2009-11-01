/*
 * PerspectiveCam.h
 *
 *  Created on: 30 oct. 2009
 *      Author: Clement
 */

#ifndef PERSPECTIVECAM_H_
#define PERSPECTIVECAM_H_

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <stdio.h>
#include "ICamera.h"
#include "Vector.h"

namespace CJEngine {

class PerspectiveCam: public ICamera {
	float _fovy;
	float _aspect;
	float _znear;
	float _zfar;

	Vector<3> _eye;
	Vector<3> _lookat;
	Vector<3> _up;

public:
	PerspectiveCam(float fovy=60.0, float aspect=1.33f, float znear=0.0001, float zfar = 10000.0);
	virtual ~PerspectiveCam();

	void SetEyePosition(const Vector<3> & eye);
	void SetLookAtPosition(const Vector<3> & lookat);
	
	virtual void Apply();
};

}

#endif /* PERSPECTIVECAM_H_ */
