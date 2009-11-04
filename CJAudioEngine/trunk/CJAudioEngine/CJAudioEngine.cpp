#include "CJAudioEngine.h"

CJAudioEngine * CJAudioEngine::_instance = 0;

CJAudioEngine::CJAudioEngine(void)
{
	_audio_engine_started = false;
	_Init();
}

CJAudioEngine::~CJAudioEngine(void)
{

}

void CJAudioEngine::_Init()
{
	//Low level initialization: OpenAL init.
	_audio_device = alcOpenDevice(NULL);
	if (_audio_device==NULL)
		return;

	_audio_context = alcCreateContext(_audio_device,NULL);
	alcMakeContextCurrent(_audio_context);
	
	InitializeCriticalSection(&_sound_list_access);
	if (CreateThread(NULL,0,_audio_refresh_thread,0,0,0)==NULL)
	{
		alcCloseDevice(_audio_device);
		return;
	}
	
	_audio_engine_started = true;
}

ISound * CJAudioEngine::CreateSound(const char * filename)
{
	ISound * newsound;

	EnterCriticalSection(&_sound_list_access);
	if (_audio_engine_started)
	{		
		newsound = new OGGSound();
		if (!newsound->Load(filename))
		{
			delete newsound;
			newsound = 0;
		}
	}
	LeaveCriticalSection(&_sound_list_access);
	return newsound;
}

CJAudioEngine * CJAudioEngine::GetInstance()
{
	if (_instance==0)
		_instance = new CJAudioEngine();

	return _instance;
}

void CJAudioEngine::_Refresh()
{
	EnterCriticalSection(&_sound_list_access);
	if (_audio_engine_started)
	{

	}
	LeaveCriticalSection(&_sound_list_access);
}

void CJAudioEngine::SetListenerPosition(float x, float y, float z)
{
	EnterCriticalSection(&_sound_list_access);
	if (_audio_engine_started)
	{
		_listener_position[0] = x;
		_listener_position[1] = y;
		_listener_position[2] = z;	
	}	
	LeaveCriticalSection(&_sound_list_access);	
}

DWORD WINAPI CJAudioEngine::_audio_refresh_thread(void * data)
{
	while (1)
	{
		Sleep(200);		
		_instance->_Refresh();
	}
}