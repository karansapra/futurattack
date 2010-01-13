#include "core.h"

///////////////////////////////////////
//Vector3
///////////////////////////////////////

Vector3::Vector3(const REAL x, const REAL y, const REAL z)
: x(x),y(y),z(z)
{
}

Vector3::Vector3(const Vector3 & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

void Vector3::Invert()
{
	x=-x;
	y=-y;
	z=-z;
}

REAL Vector3::Length() const
{
	return sqrt_real(x*x+y*y+z*z);
}

REAL Vector3::Length2() const
{
	return x*x+y*y+z*z;
}

void Vector3::Normalize()
{
	REAL length = Length();
	if (length==0)
		return;

	x /= length;
	y /= length;
	z /= length;
}

void Vector3::operator *= (const REAL value)
{
	x *= value;
	y *= value;
	z *= value;
}

Vector3 Vector3::operator * (const REAL value) const
{
	return Vector3(x*value,y*value,z*value);
}

void Vector3::operator /= (const REAL value)
{
	x /= value;
	y /= value;
	z /= value;
}

Vector3 Vector3::operator / (const REAL value) const
{
	return Vector3(x/value,y/value,z/value);
}

void Vector3::operator += (const Vector3 & v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

Vector3 Vector3::operator + (const Vector3 & v) const
{
	return Vector3(x+v.x,y+v.y,z+v.z);
}

void Vector3::operator -= (const Vector3 & v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

Vector3 Vector3::operator - (const Vector3 & v) const
{
	return Vector3(x-v.x,y-v.y,z-v.z);
}

REAL Vector3::operator * (const Vector3 & v) const
{
	return x*v.x + y*v.y + z*v.z;
}

Vector3 Vector3::operator % (const Vector3 & v) const
{
	return Vector3(
		y*v.z - z*v.y,
		z*v.x - x*v.z,
		x*v.y - y*v.x);
}

void Vector3::operator %= (const Vector3 & v)
{
	(*this) = (*this)%v;
}

void Vector3::Clear()
{
	x=0;
	y=0;
	z=0;
}

///////////////////////////////////////
//Quaternion
///////////////////////////////////////

Quaternion::Quaternion(REAL w, REAL x, REAL y, REAL z) :
w(w), x(x), y(y), z(z)
{
}

Quaternion::Quaternion(REAL theta, const Vector3 & axis)
{
	theta = theta/2;
	w = cos_real(theta);
	x = axis.x * sin_real(theta);
	y = axis.y * sin_real(theta);
	z = axis.z * sin_real(theta);
}

void Quaternion::Normalize()
{
	REAL d = w*w+x*x+y*y+z*z;

	if (d==0)
	{
		w  = 1;
		return;
	}

	d = (REAL)1.0/sqrt_real(d);
	w *= d;
	x *= d;
	y *= d;
	z *= d;
}

Quaternion Quaternion::operator * (const Quaternion & q) const
{
	return Quaternion(
		w*q.w - x*q.x - y*q.y - z*q.z,
		w*q.x + x*q.w + y*q.z - z*q.y,
		w*q.y + y*q.w + z*q.x - x*q.z,
		w*q.z + z*q.w + x*q.y - y*q.x		
		);
}

void Quaternion::operator *= (const Quaternion & q)
{
	Quaternion r = *this;
	(*this) = r*q;
}

Quaternion Quaternion::operator * (const REAL f) const
{
	return Quaternion(w*f,x*f,y*f,z*f);
}

Quaternion Quaternion::operator + (const Quaternion & q) const
{
	return Quaternion(w+q.w,x+q.x,y+q.y,z+q.z);
}

void Quaternion::RotateByVector(const Vector3 & v)
{
	Quaternion q(0,v.x,v.y,v.z);
	(*this) *= q;
}

void Quaternion::Conjugate()
{
	x=-x;
	y=-y;
	z=-z;
}

REAL Quaternion::Length() const
{
	return sqrt_real(w*w+x*x+y*y+z*z);
}

REAL Quaternion::Length2() const
{
	return w*w+x*x+y*y+z*z;
}

void Quaternion::AddScaledVector(const Vector3 & v, REAL scale)
{
	Quaternion q(0,v.x*scale,v.y*scale,v.z*scale);
	q = q*(*this);
	w += q.w *(REAL)0.5;
	x += q.x *(REAL)0.5;
	y += q.y *(REAL)0.5;
	z += q.z *(REAL)0.5;
}

///////////////////////////////////////
//Matrix33
///////////////////////////////////////

Matrix33::Matrix33()
{
	for (int i=0;i<3*3;i++)
		data[i]=0;
}

Matrix33::Matrix33(
		const REAL a11, const REAL a12, const REAL a13,
		const REAL a21, const REAL a22, const REAL a23,
		const REAL a31, const REAL a32, const REAL a33
		)
{
	data[0] = a11; data[1] = a12; data[2] = a13;
	data[3] = a21; data[4] = a22; data[5] = a23;
	data[6] = a31; data[7] = a32; data[8] = a33;
}


Vector3 Matrix33::operator * (const Vector3 & v) const
{
	return Vector3(
		data[0] * v.x + data[1] * v.y + data[2] * v.z,
		data[3] * v.x + data[4] * v.y + data[5] * v.z,
		data[6] * v.x + data[7] * v.y + data[8] * v.z
		);
}


Matrix33 Matrix33::operator * (const Matrix33 & m) const
{
	return Matrix33(
		m11*m.m11 + m12*m.m21 + m13*m.m31,
		m11*m.m12 + m12*m.m22 + m13*m.m32,
		m11*m.m13 + m12*m.m23 + m13*m.m33,

		m21*m.m11 + m22*m.m21 + m23*m.m31,
		m21*m.m12 + m22*m.m22 + m23*m.m32,
		m21*m.m13 + m22*m.m23 + m23*m.m33,

		m31*m.m11 + m32*m.m21 + m33*m.m31,
		m31*m.m12 + m32*m.m22 + m33*m.m32,
		m31*m.m13 + m32*m.m23 + m33*m.m33
		);
}

Matrix33 Matrix33::operator * (const REAL scalar) const
{
	Matrix33 m;
	for (int i=0;i<3*3;i++)
		m.data[i]=data[i]*scalar;
	return m;
}

Matrix33 Matrix33::Inverse() const
{
	REAL det = m11*m22*m33 + m21*m32*m13 + m31*m12*m23
		- (m11*m32*m23 + m31*m22*m13 + m21*m12*m33);

	if (det==0)
		return Matrix33();

	det = (REAL)1.0/det;

	return Matrix33(
		m22*m33-m23*m32,
		m13*m32-m12*m33,
		m12*m23-m13*m22,

		m23*m31-m21*m33,
		m11*m33-m13*m31,
		m13*m21-m11*m23,

		m21*m32-m22*m31,
		m12*m31-m11*m32,
		m11*m22-m12*m21
		)*det;
}

Matrix33 Matrix33::Transpose() const
{
	return Matrix33(
		m11, m21, m31,
		m12, m22, m32,
		m13, m23, m33
		);
}

void Matrix33::Clear()
{
	for (int i=0;i<3*3;i++)
		data[i]=0;
}

void Matrix33::SetOrientation(const Quaternion & q)
{
	m11 = 1 - 2*(q.y*q.y+q.z*q.z);
	m12 = 2*(q.x*q.y-q.z*q.w);
	m13 = 2*(q.x*q.z+q.y*q.w);

	m21 = 2*(q.x*q.y+q.z*q.w);
	m22 = 1 - 2*(q.x*q.x+q.z*q.z);
	m23 = 2*(q.y*q.z-q.x*q.w);

	m31 = 2*(q.x*q.z-q.y*q.w); 
	m32 = 2*(q.y*q.z+q.x*q.w);
	m33 = 1 - 2*(q.x*q.x+q.y*q.y);
}

///////////////////////////////////////
//HomogenousMatrix44
///////////////////////////////////////

HomogenousMatrix44::HomogenousMatrix44()
{
	m11=1;	m12=0;	m13=0;	m14=0;
	m21=0;	m22=1;	m23=0;	m24=0;
	m31=0;	m32=0;	m33=1;	m34=0;

	//Homogenous, so always 0 0 0 1
	m41=0;	m42=0;	m43=0;	m44=1;
}

HomogenousMatrix44::HomogenousMatrix44(
	const REAL a11, const REAL a12, const REAL a13, const REAL a14,
	const REAL a21, const REAL a22, const REAL a23, const REAL a24,
	const REAL a31, const REAL a32, const REAL a33, const REAL a34
	)
{
	data[0] = a11; data[1] = a12; data[2] = a13; data[3] = a14;
	data[4] = a21; data[5] = a22; data[6] = a23; data[7] = a24;
	data[8] = a31; data[9] = a32; data[10] = a33; data[11] = a34;

	m41 = 0;	m42 = 0;	m43 = 0;	m44 = 1;
}

Vector3 HomogenousMatrix44::operator * (const Vector3 & v) const
{
	return Vector3(
		m11 * v.x + m12*v.y + m13*v.z + m14,
		m21 * v.x + m22*v.y + m23*v.z + m24,
		m31 * v.x + m32*v.y + m33*v.z + m34
		);
}

HomogenousMatrix44 HomogenousMatrix44::operator * (const HomogenousMatrix44 & m) const
{
	return HomogenousMatrix44(
		m11*m.m11 + m12*m.m21 + m13*m.m31,
		m11*m.m12 + m12*m.m22 + m13*m.m32,
		m11*m.m13 + m12*m.m23 + m13*m.m33,
		m11*m.m14 + m12*m.m24 + m13*m.m34 + m14,

		m21*m.m11 + m22*m.m21 + m23*m.m31,
		m21*m.m12 + m22*m.m22 + m23*m.m32,
		m21*m.m13 + m22*m.m23 + m23*m.m33,
		m21*m.m14 + m22*m.m24 + m23*m.m34 + m24,

		m31*m.m11 + m32*m.m21 + m33*m.m31,
		m31*m.m12 + m32*m.m22 + m33*m.m32,
		m31*m.m13 + m32*m.m23 + m33*m.m33,
		m31*m.m14 + m32*m.m24 + m33*m.m34 + m34
		);
}

Matrix33 HomogenousMatrix44::operator * (const Matrix33 & m) const
{
	return Matrix33(
		m11*m.m11 + m12*m.m21 + m13*m.m31,
		m11*m.m12 + m12*m.m22 + m13*m.m32,
		m11*m.m13 + m12*m.m23 + m13*m.m33,

		m21*m.m11 + m22*m.m21 + m23*m.m31,
		m21*m.m12 + m22*m.m22 + m23*m.m32,
		m21*m.m13 + m22*m.m23 + m23*m.m33,

		m31*m.m11 + m32*m.m21 + m33*m.m31,
		m31*m.m12 + m32*m.m22 + m33*m.m32,
		m31*m.m13 + m32*m.m23 + m33*m.m33
		);
}

HomogenousMatrix44 HomogenousMatrix44::operator * (const REAL scalar) const
{
	HomogenousMatrix44 m;
	for (int i=0;i<3*4;i++)
		m.data[i]=data[i]*scalar;
	return m;
}

HomogenousMatrix44 HomogenousMatrix44::Inverse() const
{	
	REAL det =
		m11*(m22*m33-m23*m32)-
		m21*(m12*m33-m13*m32)+
		m31*(m12*m23-m13*m22);

	if (det==0)
		return HomogenousMatrix44();

	det = (REAL)1.0/det;
	
	HomogenousMatrix44 m;

	m.data[0] = (-data[9]*data[6]+data[5]*data[10])*det;
	m.data[4] = (data[8]*data[6]-data[4]*data[10])*det;
	m.data[8] = (-data[8]*data[5]+data[4]*data[9])*det;

	m.data[1] = (data[9]*data[2]-data[1]*data[10])*det;
	m.data[5] = (-data[8]*data[2]+data[0]*data[10])*det;
	m.data[9] = (data[8]*data[1]-data[0]*data[9])*det;

	m.data[2] = (-data[5]*data[2]+data[1]*data[6])*det;
	m.data[6] = (+data[4]*data[2]-data[0]*data[6])*det;
	m.data[10] = (-data[4]*data[1]+data[0]*data[5])*det;

	m.data[3] = (data[9]*data[6]*data[3]
			   -data[5]*data[10]*data[3]
			   -data[9]*data[2]*data[7]
			   +data[1]*data[10]*data[7]
			   +data[5]*data[2]*data[11]
			   -data[1]*data[6]*data[11])*det;
	m.data[7] = (-data[8]*data[6]*data[3]
			   +data[4]*data[10]*data[3]
			   +data[8]*data[2]*data[7]
			   -data[0]*data[10]*data[7]
			   -data[4]*data[2]*data[11]
			   +data[0]*data[6]*data[11])*det;
	m.data[11] =(data[8]*data[5]*data[3]
			   -data[4]*data[9]*data[3]
			   -data[8]*data[1]*data[7]
			   +data[0]*data[9]*data[7]
			   +data[4]*data[1]*data[11]
			   -data[0]*data[5]*data[11])*det;
	
	return m;
}

Matrix33 HomogenousMatrix44::ReturnRotationMatrix() const
{
	return Matrix33(
		m11,m12,m13,
		m21,m22,m23,
		m31,m32,m33
		);
}

void HomogenousMatrix44::SetOrientationAndPosition(const Quaternion & q, const Vector3 & position)
{
	m11 = 1 - 2*(q.y*q.y+q.z*q.z);
	m12 = 2*(q.x*q.y-q.z*q.w);
	m13 = 2*(q.x*q.z+q.y*q.w);

	m21 = 2*(q.x*q.y+q.z*q.w);
	m22 = 1 - 2*(q.x*q.x+q.z*q.z);
	m23 = 2*(q.y*q.z-q.x*q.w);

	m31 = 2*(q.x*q.z-q.y*q.w); 
	m32 = 2*(q.y*q.z+q.x*q.w);
	m33 = 1 - 2*(q.x*q.x+q.y*q.y);

	m14 = position.x;
	m24 = position.y;
	m34 = position.z;
}

void HomogenousMatrix44::SetPosition(const Vector3 & position)
{
	m11=1; m12=0; m13=0; m14=position.x;
	m21=0; m22=1; m23=0; m24=position.y;
	m31=0; m32=0; m33=1; m34=position.z;
	m41=0; m42=0; m43=0; m44=1;
}

void HomogenousMatrix44::FillOpenGLMatrix(REAL * glmatrix)
{
	glmatrix[0] = m11;
	glmatrix[1] = m21;
	glmatrix[2] = m31;
	glmatrix[3] = m41;

	glmatrix[4] = m12;
	glmatrix[5] = m22;
	glmatrix[6] = m32;
	glmatrix[7] = m42;

	glmatrix[8] = m13;
	glmatrix[9] = m23;
	glmatrix[10] = m33;
	glmatrix[11] = m43;

	glmatrix[12] = m14;
	glmatrix[13] = m24;
	glmatrix[14] = m34;
	glmatrix[15] = m44;
}

Vector3 HomogenousMatrix44::TransformDirection(const Vector3 & direction) const
{
	return Vector3(
		direction.x * m11 + direction.y * m12 + direction.z * m13,
		direction.x * m21 + direction.y * m22 + direction.z * m23,
		direction.x * m31 + direction.y * m32 + direction.z * m33
		);
}




Vector3 LocalToWorldTransform(const Vector3 &local, const HomogenousMatrix44 &transform)
{
	return transform * local;
}

Vector3 WorldToLocalTransform(const Vector3 &world, const HomogenousMatrix44 &transform)
{
	HomogenousMatrix44 inverse;
	inverse = transform.Inverse();
	return inverse*world;
}

