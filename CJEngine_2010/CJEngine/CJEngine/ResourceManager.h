#pragma once
#include <vector>
#include "./Resource.h"
#include "./Texture.h"

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
};
