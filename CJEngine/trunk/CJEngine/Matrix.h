#pragma once

#include "Vector.h"

namespace CJEngine
{
	class Matrix44
	{
		float * _matrix;
		float _zero;	

	public:

		Matrix44(void)
		{
			_matrix = new float[16];
			_zero = 0.0f;
			for (int i=0;i<16;i++)
				_matrix[i] = 0.0f;
		}

		Matrix44(Matrix44 & m)
		{
			_matrix = new float[16];
			_zero = 0.0f;
			for (int i=0;i<16;i++)
				_matrix[i] = m._matrix[i];
		}

		Vector<4> operator * (Vector<4> & v)
		{
			Vector<4> result;

			for (int y=0;y<4;y++)
				for (int x=0;x<4;x++)
					result[y] += (*this)(y,x)*v[x];

			return result;
		}

		float & operator () (int m, int n)
		{
			if (m<4 && n<4 && m>=0 && n>=0)
				return _matrix[n*4+m];
			return _zero;
		}

		Matrix44 operator * (Matrix44 &m)
		{
			Matrix44 result;
			float sum;

			for (int y=0;y<4;y++)
			{
				for (int x=0;x<4;x++)
				{
					sum = 0.0f;

					for (int i=0;i<4;i++)
						sum+=(*this)(y,i) * m(i,x);

					result(y,x) = sum;
				}
			}

			return result;
		}

		float * GetData()
		{
			return _matrix;
		}

		void Identity()
		{
			for (int i=0;i<16;i++)
				_matrix[i] = 0.0f;
			_matrix[0] = 1.0f;
			_matrix[5] = 1.0f;
			_matrix[10] = 1.0f;
			_matrix[15] = 1.0f;
		}

		void DbgPrint()
		{
			for (int y=0;y<4;y++)
			{
				for (int x=0;x<4;x++)
				{
					printf("%.3f ",(*this)(y,x));
				}
				printf("\n");
			}
			printf("\n");
		}

		Matrix44 & operator = (const Matrix44 & m)
		{
			for (int i=0;i<16;i++)
				_matrix[i] = m._matrix[i];

			return (*this);
		}

		~Matrix44(void)
		{
			delete[] _matrix;
		}
	};

}
