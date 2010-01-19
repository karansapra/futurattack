using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TornadoEngineTools
{
    class Vector3
    {
        public float x, y, z;

        /*
         * Default constructor, initialize with null vector (0,0,0)
         */ 
        public Vector3()
        {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }

        public Vector3(float X, float Y, float Z)
        {
            x = X;
            y = Y;
            z = Z;
        }

        /*
         * Returns the norm
         */ 
        public float Length()
        {
            return (float)Math.Sqrt((double)x * x + y * y + z * z);
        }

        /*
         * Returns the norm*norm
         */ 
        public float Length2()
        {
            return x * x + y * y + z * z;
        }

        /*
         * Normalization of the vector
         */ 
        public void Normalize()
        {
            float d = Length();
            x /= d;
            y /= d;
            z /= d;
        }

        /*
         * Standard addition
         */ 
        public static Vector3 operator +(Vector3 a, Vector3 b)
        {
            return new Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
        }

        /*
         * Standard substraction
         */ 
        public static Vector3 operator -(Vector3 a, Vector3 b)
        {
            return new Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
        }

        /*
         * Scalar product
         */ 
        public static float operator *(Vector3 a, Vector3 b)
        {
            return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
        }

        /*
         * Multiplication by a scalar value
         */
        public static Vector3 operator *(Vector3 a, float s)
        {            
            return new Vector3(a.x * s, a.y * s, a.z * s);
        }

        /*
         * Division by a scalar value
         */
        public static Vector3 operator /(Vector3 a, float s)
        {
            return new Vector3(a.x / s, a.y / s, a.z / s);
        }

        /*
         * Cross product
         */ 
        public static Vector3 operator %(Vector3 a, Vector3 b)
        {
            return new Vector3(
                (a.y*b.z)-(a.z*b.y),
                (a.z*b.x)-(a.x*b.z),
                (a.x*b.y)-(a.y*b.x)
                );
        }

        /*
         * Returns the inverse of the current vector
         */ 
        public Vector3 GetInverse()
        {
            return new Vector3(-x, -y, -z);
        }

        /*
         * Inverts the current vector
         */ 
        public void Inverse()
        {
            x *= -1.0f;
            y *= -1.0f;
            z *= -1.0f;
        }

    }

}
