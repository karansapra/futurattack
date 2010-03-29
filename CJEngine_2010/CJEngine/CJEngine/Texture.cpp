#include "./Texture.h"
#include "./Core.h"

Texture::Texture(const char * filename)
{
	format_ = 0;
	size_t size;
	wchar_t wfilename[256];
	mbstowcs_s(&size,wfilename,256,filename,256);
	Gdiplus::Bitmap bmp(wfilename);
	width_ = bmp.GetWidth();
	height_ = bmp.GetHeight();
	if (width_==0 || height_==0)
		return;
	Gdiplus::Rect locked_region(0,0,width_,height_);
	Gdiplus::BitmapData data;
	
	if (bmp.LockBits(&locked_region,Gdiplus::ImageLockModeRead,PixelFormat32bppARGB,&data)!=Gdiplus::Ok)
		return;
	format_ = 4;
	stride_ = data.Stride;
	data_ = new unsigned char[stride_*height_];
	CopyMemory(data_,data.Scan0,stride_*height_);
	bmp.UnlockBits(&data);

	glGenTextures(1,&gltexture_id_);
	glBindTexture(GL_TEXTURE_2D,gltexture_id_);
	glTexImage2D(GL_TEXTURE_2D,0,4,width_,height_,0,GL_BGRA_EXT,GL_UNSIGNED_BYTE,data_);
}

Texture::~Texture(void)
{
	delete[] data_;
}

unsigned int Texture::GetWidth()
{
	return width_;
}

unsigned int Texture::GetHeight()
{
	return height_;
}