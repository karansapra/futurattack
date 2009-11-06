#pragma once

#include "CJAudioEngineSystem.h"
#include "IOpenAL.h"

#include "ISound.h"
#include "OGGSound.h"

#include "IMusic.h"
#include "OGGMusic.h"

class DLL_LOAD CJAudioEngine : public IOpenAL
{
	//Ctors and Dtors
	CJAudioEngine(void);
	~CJAudioEngine(void);

	//OpenAL initialization
	void _Init();

	//Singleton instance of AudioEngine
	static CJAudioEngine * _instance;

	bool _audio_engine_started;
	ALCdevice * _audio_device;
	ALCcontext * _audio_context;

	float _listener_position[3];

	ISound * _isoundlist[MAX_SOUNDS];

public:	
	//Returns the unique instance of the singleton
	static CJAudioEngine * GetInstance();

	void SetListenerPosition(float x, float y, float z);
	ISound * CreateSound(const char * filename);
	IMusic * CreateMusic(const char * filename);
};

