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


void ITexture::_endian_convert(DWORD & d)
{
	DWORD d_buf;
	unsigned char * d_char = (unsigned char *)&d;
	d_buf = (d_char[0]<<24) + (d_char[1]<<16) + (d_char[2]<<8) + (d_char[3]);
	d = d_buf;
}

void ITexture::_endian_convert(WORD & d)
{
	WORD d_buf;
	unsigned char * d_char = (unsigned char *)&d;
	d_buf = (d_char[0]<<8) + (d_char[1]);
	d = d_buf;
}

