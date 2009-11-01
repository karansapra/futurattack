/*
 * Quaternion.cpp
 *
 *  Created on: 30 oct. 2009
 *      Author: Clement
 */

#include "Quaternion.h"

namespace CJEngine {

	Quaternion::Quaternion(float w, float x, float y, float z) {
		_w = w;
		_x = x;
		_y = y;
		_z = z;
	}

	Quaternion Quaternion::operator +(Quaternion & q)
	{
		Quaternion q2;
		q2._w = _w + q._w;
		q2._x = _x + q._x;
		q2._y = _y + q._y;
		q2._z = _z + q._z;
		return q2;
	}

	Quaternion & Quaternion::operator = (const Quaternion & q)
	{
		_w = q._w;
		_x = q._x;
		_y = q._y;
		_z = q._z;
		return (*this);
	}

	Quaternion Quaternion::operator -(Quaternion & q)
	{
		Quaternion q2;
		q2._w = _w - q._w;
		q2._x = _x - q._x;
		q2._y = _y - q._y;
		q2._z = _z - q._z;
		return q2;
	}

	Quaternion Quaternion::operator *(const Quaternion & q)
	{
		Quaternion q2;
		q2._w = _w * q._w - (
				_x*q._x +
				_y*q._y +
				_z*q._z
				);

		q2._x = _w * q._x + q._w * _x + _y*q._z - _z*q._y;
		q2._y = _w * q._y + q._w * _y + _z*q._x - _x*q._z;
		q2._z = _w * q._z + q._w * _z + _x*q._y - _y*q._x;

		return q2;
	}

	Quaternion Quaternion::operator *(float f)
	{
		Quaternion q2;
		q2._w = _w*f;
		q2._x = _x*f;
		q2._y = _y*f;
		q2._z = _z*f;
		return q2;
	}

	Matrix44 Quaternion::GetMatrix44()
	{
		Matrix44 m;

		float x2 = _x*_x;
		float y2 = _y*_y;
		float z2 = _z*_z;

		float xy = _x*_y;
		float xz = _x*_z;
		float yz = _y*_z;

		float wz = _w*_z;
		float wy = _w*_y;
		float wx = _w*_x;

		m(0,0) = 1.0f-2.0f*(y2+z2);	m(0,1) = 2.0f*(xy-wz);		m(0,2) = 2.0f*(xz+wy);
		m(1,0) = 2.0f*(xy+wz);		m(1,1) = 1.0f-2.0f*(x2+z2); m(1,2) = 2.0f*(yz-wx);
		m(2,0) = 2.0f*(xz-wy);		m(2,1) = 2.0f*(yz+wx);		m(2,2) = 1.0f-2.0f*(x2+y2);

		m(3,3) = 1.0f;

		return m;
	}

	Quaternion Quaternion::LERP(const Quaternion & a, const Quaternion & b, float t)
	{
		Quaternion q;		
		q=(Quaternion)a*(1.0f-t)+(Quaternion)b*t;
		return q;
	}

	Quaternion Quaternion::SLERP(const Quaternion & a, const Quaternion & b, float t)
	{
		float theta = acos(
			a._w*b._w+
			a._x*b._x+
			a._y*b._y+
			a._z*b._z);
		
		float stheta = sin(theta);
		float acoeff = sin((1.0f-t)*theta)/stheta;
		float bcoeff = sin(t*theta)/stheta;
		Quaternion q;
		q=(Quaternion)a*acoeff+(Quaternion)b*bcoeff;
		return q;
	}	

	Quaternion Quaternion::FromEulerAngles(float x, float y, float z)
	{
		x = x/2.0f;
		y = y/2.0f;
		z = z/2.0f;

		float c1 = cos(y);
		float c2 = cos(z);
		float c3 = cos(x);

		float s1 = sin(y);
		float s2 = sin(z);
		float s3 = sin(x);

		Quaternion qfinal(
			c1*c2*c3-s1*s2*s3,
			s1*s2*c3+c1*c2*s3,
			s1*c2*c3+c1*s2*s3,
			c1*s2*c3-s1*c2*s3);
		printf("New Quaternion : Q=[%f, %f, %f, %f]\n",qfinal._w,qfinal._x,qfinal._y,qfinal._z);
		return qfinal;
	}

	Quaternion Quaternion::Conjugate()
	{
		Quaternion q;
		q._w = _w;
		q._x = -_x;
		q._y = -_y;
		q._z = -_z;
		return q;
	}

	Quaternion::~Quaternion() {
	}

}
