#ifndef USRMatrix_h__
#define USRMatrix_h__

#include "USRVector3.h"
#include <math.h>

/**
\brief Matrix used in 3d maths
*/
class USRMatrix
{
public:
	USRMatrix()
	{
		for (int i=0;i<16;i++)
			_m[i] = 0;

		_m[0] = 1;
		_m[5] = 1;
		_m[10] = 1;
		_m[15] = 1;
	}

	USRVector3 operator*(USRVector3 & v)
	{
		USRVector3 result;

		for (unsigned int c=0;c<4;c++)
		{
			for (unsigned int x=0;x<4;x++)
				result.Values[c] += v.Values[x]*GetValue(x,c);
		}

		return result;
	}

	USRMatrix operator*(USRMatrix & m)
	{
		USRMatrix result;

		for (unsigned int y=0;y<4;y++)
		{
			for (unsigned int x=0;x<4;x++)
			{
				result.GetValue(x,y) = 0;
				for (unsigned int i=0;i<4;i++)	
					result.GetValue(x,y) += GetValue(i,y) * m.GetValue(x,i);
			}
		}

		return result;
	}

	void Translate(USRVector3 & t)
	{
		USRMatrix tm = CreateTranslationMatrix(t);
		USRMatrix res = (*this)*tm;
		memcpy(_m,res._m,sizeof(float)*16);
	}

	static USRMatrix CreateTranslationMatrix(USRVector3 & t)
	{
		USRMatrix m;

		m[12] = t.X;
		m[13] = t.Y;
		m[14] = t.Z;

		return m;
	}	

	static USRMatrix CreateZRotationMatrix(float angle)
	{
		USRMatrix m;

		float c = cosf(angle);
		float s = sinf(angle);

		m[0] = c;
		m[1] = s;

		m[4] = -s;
		m[5] = c;

		return m;
	}

	static USRMatrix CreateYRotationMatrix(float angle)
	{
		USRMatrix m;

		float c = cosf(angle);
		float s = sinf(angle);

		m[0] = c;
		m[2] = -s;

		m[8] = s;
		m[10] = c;

		return m;
	}

	static USRMatrix CreateXRotationMatrix(float angle)
	{
		USRMatrix m;

		float c = cosf(angle);
		float s = sinf(angle);

		m[5] = c;
		m[6] = s;

		m[9] = -s;
		m[10] = c;

		return m;
	}

	/**
	\brief Used to setup a Camera matrix
	*/
	static USRMatrix CreateLookAtMatrix(USRVector3 eye, USRVector3 center ,USRVector3 up)
	{
		USRVector3 ViewDirection = center-eye;
		ViewDirection.Normalize();
		up.Normalize();
		USRVector3 RightDirection = ViewDirection.CrossProduct(up);
		RightDirection.Normalize();
		up = RightDirection.CrossProduct(ViewDirection);

		USRMatrix result;

		result[0] = RightDirection.X;
		result[4] = RightDirection.Y;
		result[8] = RightDirection.Z;

		result[1] = up.X;
		result[5] = up.Y;
		result[9] = up.Z;

		result[2] = -ViewDirection.X;
		result[6] = -ViewDirection.Y;
		result[10] = -ViewDirection.Z;

		eye.Invert();
		result.Translate(eye);
/*
		result[12] = -(result[0]*eye.X + result[4]*eye.Y + result[8]*eye.Z);
		result[13] = -(result[1]*eye.X + result[5]*eye.Y + result[9]*eye.Z);
		result[14] = -(result[2]*eye.X + result[6]*eye.Y + result[10]*eye.Z);
*/
		return result;
	}

	static USRMatrix CreateWindowMatrix(float width, float height)
	{
		USRMatrix m;

		m[0] = width/2;
		m[5] = -height/2;
		m[12] = width/2;
		m[13] = height/2;

		return m;
	}

	static USRMatrix CreateOrthoProjectionMatrix(float left, float right, float bottom, float top, float near, float far)
	{
		USRMatrix m;

		m[0] = 2.0f/(right-left);
		m[5] = 2.0f/(top-bottom);
		m[10] = 1.0f/(far-near);

		m[12] = (right+left)/(left-right);
		m[13] = (top+bottom)/(bottom-top);
		m[14] = near/(near-far);

		return m;
	}

	static USRMatrix CreateProjectionMatrix(float left, float right, float bottom, float up, float near, float far)
	{
		USRMatrix m;

		m[0] = (2.0f*near)/(right-left);
		m[5] = (2.0f*near)/(up-bottom);
		m[10] = (far)/(far-near);
		m[11] = 1;
		m[15] = 0;		
		m[14] = (-near*far)/(far-near);

		return m;
	}

	static USRMatrix CreateScaleMatrix(USRVector3 & scale)
	{
		USRMatrix m;

		m[0] = scale.X;
		m[5] = scale.Y;
		m[10] = scale.Z;

		return m;
	}

private:
	float _m[16];

	inline float & operator[](unsigned int index)
	{
		return _m[index];
	}

	inline float & GetValue(unsigned int x,unsigned int y)
	{
		return _m[(x<<2)+y];
	}
};

#endif // USRMatrix_h__