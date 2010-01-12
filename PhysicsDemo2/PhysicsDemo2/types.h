#ifndef TYPES_H
#define TYPES_H

#include <math.h>
#include <vector>

//Types
typedef float			REAL;
typedef unsigned char	U8;
typedef unsigned short	U16;
typedef unsigned int	U32;

typedef U8*				PTR;

//Function pointers
typedef void (*PFUNC)(void);

//Usefull mathematics functions
#define sqrt_real		sqrtf
#define pow_real		powf
#define abs_real		fabsf
#define sin_real		sinf
#define cos_real		cosf

//Mathematics constants
const float pi_real	=	3.14159265358979323846f;
const float pi_real2 =	pi_real/2.0f;

struct XY
{
	U32 x;
	U32 y;

	XY()
	{
		x=0;
		y=0;
	}
};

#endif