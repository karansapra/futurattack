#pragma once

class TextNode;
class Font
{
	friend class TextNode;

	unsigned int gllist;
public:
	Font(const char * fontname, int size);
	~Font(void);
};
