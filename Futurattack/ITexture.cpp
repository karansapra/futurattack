/*
 * ITexture.cpp
 *
 *  Created on: 2 oct. 2009
 *      Author: clement
 */

#include "ITexture.h"

ITexture::ITexture() {
	// TODO Auto-generated constructor stub
	_width = 0;
	_height = 0;
	_bpp = 0;
	_pixels_data = NULL;
}

ITexture::~ITexture() {
	// TODO Auto-generated destructor stub
}

int ITexture::GetWidth()
{
	return _width;
}



char *ITexture::GetPixelsData()
{
	return _pixels_data;
}



int ITexture::GetBPP()
{
	return _bpp;
}



int ITexture::GetHeight()
{
	return _height;
}



const char *ITexture::ToString()
{
	return "ITexture";
}


