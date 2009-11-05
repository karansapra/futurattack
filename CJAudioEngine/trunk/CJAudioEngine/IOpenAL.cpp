#include "IOpenAL.h"

CRITICAL_SECTION * IOpenAL::_openal_access = 0;

IOpenAL::IOpenAL(void)
{
	if (_openal_access==0)
		_openal_access = new CRITICAL_SECTION;

	InitializeCriticalSection(_openal_access);
}

IOpenAL::~IOpenAL(void)
{
	
}
