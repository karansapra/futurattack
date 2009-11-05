#pragma once

#include "IOpenAL.h"
#include "IMusic.h"

class OGGMusic :
	public IMusic, public IOpenAL
{
	enum PlayingState {PLAY,PAUSE,STOP};
	PlayingState _current_playing_state;

	OggVorbis_File _ogg_file;

	HANDLE _state_changed;
	static DWORD WINAPI _thread_play_pause_stop_wrapper(void * data);
	void _thread_play_pause_stop();

	int total_reads;
	int actual_reads;
	int bitstream;
	ALuint buffer_unqueue;
	ALint nprocessed;

public:
	OGGMusic(void);
	virtual ~OGGMusic(void);

	bool Load(const char * filename);
	void Play();
	void Pause();
	void Stop();
};
