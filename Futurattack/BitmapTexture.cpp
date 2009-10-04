/*
 * BitmapTexture.cpp
 *
 *  Created on: 4 oct. 2009
 *      Author: clement
 */

#include "BitmapTexture.h"

BitmapTexture::BitmapTexture() : ITexture() {

}

BitmapTexture::~BitmapTexture() {
	if (_pixels_data!=NULL)
		delete[] _pixels_data;
}

bool BitmapTexture::Load(const char *filename)
{
	FILE * f = fopen(filename,"r");
	if (f==NULL)
		return false;

	//On lit le header du fichier
	BitmapFileHeader bfheader;
	BitmapHeader bheader;

	//Si la signature du fichier est incorrecte, ce n'est pas un Bitmap, on sort
	fread(&bfheader,1,sizeof(BitmapFileHeader),f);
	_endian_convert(bfheader.Signature);
	if (bfheader.Signature!=0x424D)
	{
		fclose(f);
		return false;
	}

	//Si le test a passé, on peut acquérir la suite du fichier
	fread(&bheader,1,sizeof(BitmapHeader),f);
	//Si on ne passe pas ces tests, on ne sait pas traiter le fichier, donc on quitte
	if (bheader.HeaderSize!=0x28 || bheader.CompressionMethod!=0 || bheader.PlansCount!=1 || bheader.BPP<24)
	{
		fclose(f);
		return false;
	}

	//Definition des attributs
	_width = bheader.Width;
	_height = bheader.Height;
	_bpp = bheader.BPP;

	//Allocating memory for pixels values
	unsigned char * temp_pixel_data = new unsigned char[bheader.ImageSize];
	_pixels_data = new char[_width*_height*(_bpp/8)];

	//On positionne la lecture du fichier au debut des donnees Bitmap
	fseek(f,bfheader.BitmapOffset,SEEK_SET);

	//On lit les données bitmap des pixels
	fread(temp_pixel_data,1,bheader.ImageSize,f);

	//On clos le fichier
	fclose(f);

	//On formatte correctement le fichier pour nos besoins
	int byte_per_pixel = (_bpp/8);
	int line_length = _width*byte_per_pixel;
	if ((_width*byte_per_pixel/4)*4!=(_width*byte_per_pixel))
		line_length = ((_width*byte_per_pixel/4)+1)*4;

	for (int y=0;y<_height;y++)
	{
		memcpy(&_pixels_data[_width*y*byte_per_pixel],&temp_pixel_data[(_height-y-1)*line_length],_width*byte_per_pixel);
	}

	//On remet en mode RGB au lieu de BGR
	char temp;
	for (int i=0;i<_width*_height*(_bpp/8);i+=3)
	{
		temp = _pixels_data[i+2];
		_pixels_data[i+2] = _pixels_data[i];
		_pixels_data[i] = temp;
	}

	//Tout s'est bien passé
	delete[] temp_pixel_data;
	return true;
}



const char *BitmapTexture::ToString()
{
	return "BitmapTexture";
}


