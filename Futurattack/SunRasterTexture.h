/*
 * SunRasterTexture.h
 *
 *  Created on: 2 oct. 2009
 *      Author: clement
 */

#ifndef SUNRASTERTEXTURE_H_
#define SUNRASTERTEXTURE_H_

#include "ITexture.h"

typedef unsigned int DWORD;

struct SunRasterHeader
{
	DWORD MagicNumber;
	DWORD Width;
	DWORD Height;
	DWORD Depth;
	DWORD Length;
	DWORD Type;
	DWORD ColorMapType;
	DWORD ColorMapLength;
};

class SunRasterTexture: public ITexture {
	void _endian_convert(DWORD & d);
public:
	SunRasterTexture();
	virtual ~SunRasterTexture();

	bool Load(const char * filename);

	const char * ToString();
};

#endif /* SUNRASTERTEXTURE_H_ */
