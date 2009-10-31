/*
 * Quaternion.h
 *
 *  Created on: 30 oct. 2009
 *      Author: Clement
 */

#ifndef QUATERNION_H_
#define QUATERNION_H_

#include <math.h>
#include <stdio.h>
#include "Matrix.h"

namespace CJEngine {

class Quaternion {
	float _w,_x,_y,_z;

public:
	Quaternion(float w=0.0f, float x=0.0f, float y=0.0f, float z=0.0f);

	Quaternion & operator = (const Quaternion & q);
	Quaternion operator + (Quaternion & q);
	Quaternion operator - (Quaternion & q);
	Quaternion operator * (const Quaternion & q);
	Quaternion operator * (float f);
	Matrix44 GetMatrix44();
	Quaternion Conjugate();

	static Quaternion LERP(const Quaternion & a, const Quaternion & b, float t);
	static Quaternion SLERP(const Quaternion & a, const Quaternion & b, float t);
	static Quaternion FromEulerAngles(float x, float y, float z);

	virtual ~Quaternion();
};

}

#endif /* QUATERNION_H_ */
