/*
 * ITexture.h
 *
 *  Created on: 28 oct. 2009
 *      Author: Clement
 */

#ifndef ITEXTURE_H_
#define ITEXTURE_H_

#include <stdio.h>

namespace CJEngine {

typedef unsigned int DWORD;
typedef unsigned short WORD;


class ITexture {
protected:
	unsigned char * _pixels_data;
	int _width, _height;
	int _bpp;

	void _endian_convert(DWORD & d);
	void _endian_convert(WORD & d);

public:
	ITexture();
	virtual ~ITexture();

    virtual bool Load(const char * filename)=0;

    int GetWidth();
    int GetHeight();
    int GetBPP();
    unsigned char * GetPixelsData();
};

}

#endif /* ITEXTURE_H_ */
