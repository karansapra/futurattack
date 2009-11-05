#include "CJAudioEngine.h"

CJAudioEngine * CJAudioEngine::_instance = 0;

CJAudioEngine::CJAudioEngine(void) : IOpenAL()
{	
	_audio_engine_started = false;
	_Init();
}

CJAudioEngine::~CJAudioEngine(void)
{
	delete _openal_access;
}

void CJAudioEngine::_Init()
{
	EnterCriticalSection(_openal_access);
	//Low level initialization: OpenAL init.
	_audio_device = alcOpenDevice(NULL);
	LeaveCriticalSection(_openal_access);
	if (_audio_device==NULL)
		return;


	EnterCriticalSection(_openal_access);
	_audio_context = alcCreateContext(_audio_device,NULL);
	alcMakeContextCurrent(_audio_context);
	LeaveCriticalSection(_openal_access);

	_audio_engine_started = true;
}

ISound * CJAudioEngine::CreateSound(const char * filename)
{
	ISound * newsound;

	if (_audio_engine_started)
	{		
		newsound = new OGGSound();
		
		if (!newsound->Load(filename))
		{
			delete newsound;
			newsound = 0;
		}
	}
	return newsound;
}

CJAudioEngine * CJAudioEngine::GetInstance()
{
	if (_instance==0)
		_instance = new CJAudioEngine();

	return _instance;
}

void CJAudioEngine::SetListenerPosition(float x, float y, float z)
{
	if (_audio_engine_started)
	{
		_listener_position[0] = x;
		_listener_position[1] = y;
		_listener_position[2] = z;	
	}	
}
