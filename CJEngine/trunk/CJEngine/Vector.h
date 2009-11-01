#pragma once

namespace CJEngine
{
	template <int size>
	class Vector
	{
		float * _v;
		float _zero;

	public:

		Vector(void)
		{
			_v = new float[size];
			_zero = 0.0;
			for (int i=0;i<size;i++)
				(*this)[i]=0.0;
		}

		Vector(Vector &v)
		{
			_v = new float[size];
			_zero = 0.0;
			for (int i=0;i<size;i++)
				(*this)[i]=v[i];
		}

		void DbgPrint()
		{
			for (int i=0;i<size;i++)
				printf("%.3f ",_v[i]);
			printf("\n\n");
		}

		float Abs()
		{
			float _abs = 0.0;
			for (int i=0;i<size;i++)
				_abs += _v[i] * _v[i];
			return sqrt(_abs);
		}

		Vector & operator = (const Vector &v)
		{
			for (int i=0;i<size;i++)
				_v[i]=v._v[i];

			return (*this);
		}

		float & operator [] (int i)
		{
			if (i<size && i>=0)
				return _v[i];
			return _zero;
		}

		Vector operator - (Vector v)
		{
			Vector vresult;

			for (int i=0;i<size;i++)
				vresult[i]= (*this)[i]-v[i];

			return vresult;
		}

		Vector operator + (Vector v)
		{
			Vector vresult;

			for (int i=0;i<size;i++)
				vresult[i]= (*this)[i]+v[i];

			return vresult;
		}

		Vector operator * (float scalar)
		{
			Vector vresult;
			for (int i=0;i<size;i++)
				vresult[i] = (*this)[i]*scalar;

			return vresult;
		}

		//Dot product
		float operator * (Vector v)
		{
			float result=0.0;
			for (int i=0;i<size;i++)
				result+=(*this)[i] * v[i];

			return result;
		}

		~Vector(void)
		{
			delete[] _v;
		}
	};
}