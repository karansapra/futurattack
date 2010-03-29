#pragma once

template<class T>
class Vector2
{
public:
	Vector2(void) : X(0), Y(0)
	{
	}

	Vector2(T x, T y) : X(x), Y(y)
	{
	}

	Vector2(const Vector2 & v)
	{
		X = v.X;
		Y = v.Y;
	}

	Vector2 & operator=(const Vector2 & v)
	{
		X = v.X;
		Y = v.Y;
		return *this;
	}

	~Vector2(void)
	{
	}

	T X;
	T Y;

	/*
	Addition
	*/
	Vector2 operator+(const Vector2 & a) const
	{
		return Vector2<T>(X+a.X,Y+a.Y);
	}

	/*
	Addition
	*/
	Vector2 & operator+=(const Vector2 & a)
	{
		X += a.X;
		Y += a.Y;
		return *this;
	}

	/*
	Substraction
	*/
	Vector2 operator-(const Vector2 & a) const
	{
		return Vector2<T>(X-a.X,Y-a.Y);
	}

	/*
	Dot product
	*/
	T operator*(const Vector2 & a) const
	{
		return X*a.X+Y*a.Y;
	}

	/*
	Scalar multiplication
	*/
	Vector2 operator*(const T & a) const
	{
		return Vector2<T>(X*a,Y*a);
	}

	/*
	Squared absolute value
	*/
	T Abs2()
	{
		return X*X+Y*Y;
	}

};
