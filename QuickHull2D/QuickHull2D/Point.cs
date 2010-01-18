using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QuickHull2D
{
    class Vector2
    {
        public float x;
        public float y;

        public Vector2()
        {
            x = 0.0f;
            y = 0.0f;
        }

        public Vector2(float X, float Y)
        {
            x = X;
            y = Y;
        }
        
        public static Vector2 operator +(Vector2 a, Vector2 b)
        {
            return new Vector2(a.x+b.x,a.y+b.y);
        }

        public static Vector2 operator -(Vector2 a, Vector2 b)
        {
            return new Vector2(a.x-b.x,a.y-b.y);
        }

        //Scalar product
        public static float operator *(Vector2 a, Vector2 b)
        {
            return a.x * b.x + a.y * b.y;
        }

        //Multiplication by a scalar value
        public static Vector2 operator *(Vector2 a, float s)
        {
            return new Vector2(a.x*s,a.y*s);
        }

        //Division by a scalar value
        public static Vector2 operator /(Vector2 a, float s)
        {
            return new Vector2(a.x / s, a.y / s);
        }

        public static bool operator==(Vector2 a, Vector2 b)
        {
            return (a.x==b.x && a.y==b.y);
        }

        public static bool operator !=(Vector2 a, Vector2 b)
        {
            return (!(a.x == b.x && a.y == b.y));
        }

        public float Length()
        {
            return (float)Math.Sqrt((double)x * x + y * y);
        }

        public float Length2()
        {
            return x * x + y * y;
        }

        public void Invert()
        {
            x *= -1.0f;
            y *= -1.0f;
        }

        public void Normalize()
        {
            float d = Length();
            x /= d;
            y /= d;
        }

    }

    class Edge
    {
        public Vector2 A, B;

        public float Length2()
        {
            return (B - A).Length2();
        }

        public Vector2 GetNormal()
        {
            Vector2 AB = B-A;
            return new Vector2(-AB.y, AB.x);
        }
    }

}
