#pragma once

#include "./Resource.h"

class SpriteNode;
class Texture : public Resource
{
	friend class SpriteNode;

	unsigned int width_;
	unsigned int height_;
	int stride_;
	unsigned char format_;
	unsigned char * data_;
	unsigned int gltexture_id_;

public:
	Texture(const char * filename);
	~Texture(void);

	unsigned int GetWidth();
	unsigned int GetHeight();
};
