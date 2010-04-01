#pragma once

#include "./Resource.h"

class TextNode;
class Font : public Resource
{
	friend class TextNode;
	
	unsigned int gllist;

public:
	Font(const char * fontname, int size);
	~Font(void);
};
