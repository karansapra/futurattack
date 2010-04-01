#pragma once
#include <vector>
#include "./Resource.h"
#include "./Texture.h"
#include "./FX.h"
#include "./Font.h"

typedef std::vector<Resource*> ResourcePtrList;
typedef ResourcePtrList::iterator ResourcePtrListIterator;

class CJEngine;
class ResourceManager
{
	friend class CJEngine;

	ResourcePtrList resources_;

	ResourceManager(void);
	~ResourceManager(void);

public:
	Texture * AddTexture(const char * name);
	FX * AddEffect(const char * vert_sh_file, const char * frag_sh_file);
	Font * AddFont(const char * filename, int size);
};
