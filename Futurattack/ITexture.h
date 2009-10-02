/*
 * ITexture.h
 *
 *  Created on: 2 oct. 2009
 *      Author: clement
 */

#ifndef ITEXTURE_H_
#define ITEXTURE_H_

#include <stdio.h>
#include "BaseObject.h"

class ITexture: public BaseObject {
protected:
	char * _pixels_data;
	int _width, _height;
	int _bpp;

public:
	ITexture();
	virtual ~ITexture();

	virtual bool Load(const char * filename)=0;

	int GetWidth();
	int GetHeight();
	int GetBPP();
	char * GetPixelsData();

	const char * ToString();
};

#endif /* ITEXTURE_H_ */
