/*
 * BitmapTexture.h
 *
 *  Created on: 4 oct. 2009
 *      Author: clement
 */

#ifndef BITMAPTEXTURE_H_
#define BITMAPTEXTURE_H_

#include "ITexture.h"

#pragma pack(1)

struct BitmapFileHeader
{
	WORD Signature;
	DWORD FileSize;
	DWORD Reserved;
	DWORD BitmapOffset;
};


struct BitmapHeader
{
	DWORD HeaderSize;
	DWORD Width;
	DWORD Height;
	WORD PlansCount;
	WORD BPP;
	DWORD CompressionMethod;
	DWORD ImageSize;
	DWORD ResX;
	DWORD ResY;
	DWORD PaletteColors;
	DWORD ImportantPaletteColors;
};

class BitmapTexture: public ITexture {
public:
	BitmapTexture();
	virtual ~BitmapTexture();

	bool Load(const char * filename);

	const char * ToString();
};

#endif /* BITMAPTEXTURE_H_ */
