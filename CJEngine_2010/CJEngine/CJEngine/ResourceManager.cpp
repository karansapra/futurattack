#include "./ResourceManager.h"
#include "./Core.h"

ResourceManager::ResourceManager(void)
{
	//Loads the GDI+ library
	ULONG_PTR token;
	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartup(&token,&input,NULL);
}

ResourceManager::~ResourceManager(void)
{
	ResourcePtrListIterator i;
	for (i=resources_.begin();i!=resources_.end();i++)
	{
		delete (*i);
	}
	resources_.clear();
}

Texture * ResourceManager::AddTexture(const char * name)
{
	Texture * texture = new Texture(name);
	resources_.push_back(texture);
	return texture;
}