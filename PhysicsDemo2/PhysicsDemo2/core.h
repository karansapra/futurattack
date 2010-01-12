#ifndef CORE_H
#define CORE_H

#include "types.h"


struct Vector3
{
	union
	{
		struct
		{
			REAL x;
			REAL y;
			REAL z;
		};
		REAL values[3];
	};

	/*
	Recopy constructor. It only copy the values of
	x, y and z in the new vector
	*/
	Vector3(const Vector3 & v);

	/*
	Constructor to create a new vector.
	*/
	Vector3(const REAL x=0, const REAL y=0, const REAL z=0);

	/*
	Invert all the components of the current vector
	*/
	void Invert();

	/*
	Returns the length of the vector (norm)
	*/
	REAL Length() const;

	/*
	Returns the square of the length of the vector (norm)
	*/
	REAL Length2() const;

	/*
	Change the current vector to its normalized form
	*/
	void Normalize();

	/*
	Multiplication by a scalar value
	*/
	void operator *= (const REAL value);
	Vector3 operator * (const REAL value) const;

	/*
	Division by a scalar value
	*/
	void operator /= (const REAL value);
	Vector3 operator / (const REAL value) const;

	/*
	Addition of 2 vectors
	*/
	void operator += (const Vector3 & v);
	Vector3 operator + (const Vector3 & v) const;

	/*
	Substraction of 2 vectors
	*/
	void operator -= (const Vector3 & v);
	Vector3 operator - (const Vector3 & v) const;

	/*
	Dot product
	*/
	REAL operator * (const Vector3 & v) const;

	/*
	Cross product
	*/
	Vector3 operator % (const Vector3 & v) const;
	void operator %= (const Vector3 & v);

	/*
	Clears the vector
	*/
	void Clear();
};

struct Quaternion
{
	union
	{
		struct
		{
			REAL w;
			REAL x;
			REAL y;
			REAL z;
		};
		REAL values[4];
	};
	
	
	Quaternion(REAL w=1, REAL x=0, REAL y=0, REAL z=0);
	Quaternion(REAL theta, const Vector3 & axis);
	void Normalize();

	Quaternion operator * (const Quaternion & q) const;
	Quaternion operator * (const REAL f) const;
	Quaternion operator + (const Quaternion & q) const;
	void operator *= (const Quaternion & q);

	void AddScaledVector(const Vector3 & v, REAL scale);

	void RotateByVector(const Vector3 & v);
	void Conjugate();
	REAL Length() const;
	REAL Length2() const;
};

struct Matrix33
{
	union
	{
		struct
		{
			REAL m11;
			REAL m12;
			REAL m13;

			REAL m21;
			REAL m22;
			REAL m23;

			REAL m31;
			REAL m32;
			REAL m33;
		};
		REAL data[3*3];
	};
	

	/*
	Construction of a zero filled matrix
	*/
	Matrix33();

	/*
	Construction of matrix with given values
	*/
	Matrix33(
		const REAL a11, const REAL a12, const REAL a13,
		const REAL a21, const REAL a22, const REAL a23,
		const REAL a31, const REAL a32, const REAL a33
		);

	/*
	Multiplication of matrix 3x3 by vector 3
	*/
	Vector3 operator * (const Vector3 & v) const;

	/*
	Multiplication of two matrices 3x3
	*/
	Matrix33 operator * (const Matrix33 & m) const;

	/*
	Multiplication by a scalar
	*/
	Matrix33 operator * (const REAL scalar) const;

	/*
	Returns the inverse of the matrix or a zero filled
	matrix if the determinant is 0 and the matrix
	can't be inversed
	*/
	Matrix33 Inverse() const;

	/*
	Transpose the current matrix, and produce another
	with the transposed values
	*/
	Matrix33 Transpose() const;

	/*
	Create a rotation matrix from a quaternion
	*/
	void SetOrientation(const Quaternion & q);

	/*
	Zero fill the matrix
	*/
	void Clear();
};

/*
Homogenous Matrix 4x4 is a class to 
use this kind of matrices. You can
access only to the 12 upper values
because the last row is always (0 0 0 1)
*/
struct HomogenousMatrix44
{
	union
	{
		struct
		{
			REAL m11;
			REAL m12;
			REAL m13;
			REAL m14;

			REAL m21;
			REAL m22;
			REAL m23;
			REAL m24;

			REAL m31;
			REAL m32;
			REAL m33;
			REAL m34;

			REAL m41;
			REAL m42;
			REAL m43;
			REAL m44;				
		};			
		REAL data[4*4];
	};


	HomogenousMatrix44();
	HomogenousMatrix44(
		const REAL a11, const REAL a12, const REAL a13, const REAL a14,
		const REAL a21, const REAL a22, const REAL a23, const REAL a24,
		const REAL a31, const REAL a32, const REAL a33, const REAL a34
		);

	Vector3 operator * (const Vector3 & v) const;
	HomogenousMatrix44 operator * (const HomogenousMatrix44 & m) const;
	Matrix33 operator * (const Matrix33 & m) const;
	HomogenousMatrix44 operator * (const REAL scalar) const;

	/*
	Returns the inverse of the matrix or a zero filled
	matrix if the determinant is 0 and the matrix
	can't be inversed
	*/
	HomogenousMatrix44 Inverse() const;

	void SetOrientationAndPosition(const Quaternion & q, const Vector3 & position);
	void SetPosition(const Vector3 & position);
	void FillOpenGLMatrix(REAL * glmatrix);

	/*
	Applies only rotation transform contained in the matrix, useful for direction
	vectors, like forces
	*/
	Vector3 TransformDirection(const Vector3 & direction) const;
	Matrix33 ReturnRotationMatrix() const;
};

////////////////////////////
//  BASE CHANGE FUNCTIONS
////////////////////////////

/*
Permits to transform a local body point, to a world point
*/
Vector3 LocalToWorldTransform(const Vector3 &local, const HomogenousMatrix44 &transform);

/*
Permits to transform a world point to a local body point
*/
Vector3 WorldToLocalTransform(const Vector3 &world, const HomogenousMatrix44 &transform);


typedef std::vector<Vector3> VertexArray;





struct Mesh
{
	struct Face
	{
		U32 indexes[3];
	};	
	typedef std::vector<Face> FaceArray;

	VertexArray vertices;
	FaceArray faces;
};

#endif
