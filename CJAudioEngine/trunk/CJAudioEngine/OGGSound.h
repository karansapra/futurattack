#pragma once

#include "IOpenAL.h"
#include "ISound.h"

class DLL_LOAD OGGSound :
	public ISound, public IOpenAL
{
	enum PlayingState {PLAY,PAUSE,STOP};
	PlayingState _current_playing_state;

	OggVorbis_File _ogg_file;

	HANDLE _loaded;	
	static DWORD WINAPI _thread_loading_wrapper(void * data);
	void _thread_loading();

	HANDLE _state_changed;
	static DWORD WINAPI _thread_play_pause_stop_wrapper(void * data);
	void _thread_play_pause_stop();

public:
	OGGSound();
	virtual ~OGGSound(void);

	bool Load(const char * filename);
	void Play();
	void Pause();
	void Stop();
};

