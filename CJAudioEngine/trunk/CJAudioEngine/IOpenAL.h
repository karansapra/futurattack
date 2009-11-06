#pragma once

#include "CJAudioEngineSystem.h"

class DLL_LOAD IOpenAL
{
protected:
	static CRITICAL_SECTION * _openal_access;

	IOpenAL(void);
	virtual ~IOpenAL(void);	
};
