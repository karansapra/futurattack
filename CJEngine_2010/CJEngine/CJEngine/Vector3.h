#pragma once

template<class T>
class Vector3
{
public:
	Vector3(void) : X(0), Y(0), Z(0)
	{
	}

	Vector3(T x, T y, T z) : X(x), Y(y), Z(z)
	{
	}

	Vector3(const Vector3 & v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
	}

	Vector3 & operator=(const Vector3 & v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		return *this;
	}

	~Vector3(void)
	{
	}

	T X;
	T Y;
	T Z;

	/*
	Addition
	*/
	Vector3 operator+(const Vector3 & a) const
	{
		return Vector3<T>(X+a.X,Y+a.Y,Z+a.Z);
	}

	/*
	Substraction
	*/
	Vector3 operator-(const Vector3 & a) const
	{
		return Vector3<T>(X-a.X,Y-a.Y,Z-a.Z);
	}

	/*
	Dot product
	*/
	T operator*(const Vector3 & a) const
	{
		return X*a.X+Y*a.Y+Z*a.Z;
	}

	/*
	Scalar multiplication
	*/
	Vector3 operator*(const T & a) const
	{
		return Vector3<T>(X*a,Y*a,Z*a);
	}

	/*
	Squared absolute value
	*/
	T Abs2()
	{
		return X*X+Y*Y+Z*Z;
	}

};
