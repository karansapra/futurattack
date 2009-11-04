#pragma once

#include "CJAudioEngineSystem.h"
#include "ISound.h"
#include "OGGSound.h"

class CJAudioEngine
{
	friend class ISound;

	//Ctors and Dtors
	CJAudioEngine(void);
	~CJAudioEngine(void);
	
	//OpenAL initialization
	void _Init();

	//Singleton instance of AudioEngine
	static CJAudioEngine * _instance;
	CRITICAL_SECTION _sound_list_access;

	bool _audio_engine_started;
	ALCdevice * _audio_device;
	ALCcontext * _audio_context;

	float _listener_position[3];

	ISound * _isoundlist[MAX_SOUNDS];

	static DWORD WINAPI _audio_refresh_thread(void * data);
	void _Refresh();

public:	
	//Returns the unique instance of the singleton
	static CJAudioEngine * GetInstance();

	void SetListenerPosition(float x, float y, float z);
	ISound * CreateSound(const char * filename);

	
};
