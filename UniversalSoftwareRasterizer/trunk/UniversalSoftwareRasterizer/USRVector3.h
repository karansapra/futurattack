#ifndef USRVector3_h__
#define USRVector3_h__
#include <math.h>

class USRVector3
{
public:
        USRVector3(void) : X(0), Y(0), Z(0), I(1)
        {
        }

        USRVector3(float x, float y, float z) : X(x), Y(y), Z(z), I(1)
        {
        }

        USRVector3(const USRVector3 & v)
        {
                X = v.X;
                Y = v.Y;
                Z = v.Z;
        }

        USRVector3 & operator=(const USRVector3 & v)
        {
                X = v.X;
                Y = v.Y;
                Z = v.Z;
                return *this;
        }

        ~USRVector3(void)
        {
        }

		union
		{
			struct  
			{
				float X;
				float Y;
				float Z;
				float I;
			};

			float Values[4];
		};

        /*
        Addition
        */
        USRVector3 operator+(const USRVector3 & a) const
        {
			return USRVector3(X+a.X,Y+a.Y,Z+a.Z);
        }

        /*
        Substraction
        */
        USRVector3 operator-(const USRVector3 & a) const
        {
            return USRVector3(X-a.X,Y-a.Y,Z-a.Z);
        }

        /*
        Dot product
        */
        float operator*(const USRVector3 & a) const
        {
            return X*a.X+Y*a.Y+Z*a.Z;
        }

        /*
        Scalar multiplication
        */
        USRVector3 operator*(const float & a) const
        {
            return USRVector3(X*a,Y*a,Z*a);
        }

        /*
        Scalar multiplication
        */
        USRVector3 operator/(const float & a) const
        {
            return USRVector3(X/a,Y/a,Z/a);
        }

        /*
        Squared absolute value
        */
        float Abs2()
        {
            return X*X+Y*Y+Z*Z;
        }

		float Abs()
		{
			return sqrtf(X*X+Y*Y+Z*Z);
		}

		void Normalize()
		{
			float n = Abs();
			X /= n;
			Y /= n;
			Z /= n;
		}

		USRVector3 CrossProduct(USRVector3 & v)
		{
			USRVector3 result;
			result.X = Y*v.Z - Z*v.Y;
			result.Y = Z*v.X - X*v.Z;
			result.Z = X*v.Y - Y*v.X;
			return result;
		}
};


#endif // USRVector3_h__