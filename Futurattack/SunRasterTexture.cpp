/*
 * SunRasterTexture.cpp
 *
 *  Created on: 2 oct. 2009
 *      Author: clement
 */

#include "SunRasterTexture.h"

SunRasterTexture::SunRasterTexture() : ITexture() {
	// TODO Auto-generated constructor stub

}

SunRasterTexture::~SunRasterTexture() {
	// TODO Auto-generated destructor stub
	if (_pixels_data!=NULL)
		delete[] _pixels_data;
}

bool SunRasterTexture::Load(const char *filename)
{
	FILE * f = fopen(filename,"rb");
	if (f==NULL)
		return false;

	//On lit le header du fichier
	SunRasterHeader header;
	fread(&header,sizeof(SunRasterHeader),1,f);

	//On passe en little endian, parcque le SunRaster est un format
	//Big Endian , SUN oblige!
	for (char i=0;i<8;i++)
		_endian_convert(((DWORD*)&header)[(int)i]);

	//Plusieurs test pour confirmer le format correct
	if (header.MagicNumber!=0x59A66A95)
	{
		fclose(f);
		return false;
	}
	if (header.Type!=0x00000001)
	{
		fclose(f);
		return false;
	}
	if (header.ColorMapType!=0x00000000)
	{
		fclose(f);
		return false;
	}

	//Definition des attributs
	_width = header.Width;
	_height = header.Height;
	_bpp = header.Depth;

	//Allocating memory for pixels values
	_pixels_data = new char[_width*_height*(_bpp/8)];
	fread(_pixels_data,1,_width*_height*(_bpp/8),f);

	//On clos le fichier
	fclose(f);

	//On remet en mode RGB au lieu de BGR
	char temp;
	for (int i=0;i<_width*_height*(_bpp/8);i+=3)
	{
		temp = _pixels_data[i+2];
		_pixels_data[i+2] = _pixels_data[i];
		_pixels_data[i] = temp;
	}

	//Tout s'est bien passé
	return true;
}

const char *SunRasterTexture::ToString()
{
	return "SunRasterTexture";
}


