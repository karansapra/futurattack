#pragma once

#include "CJAudioEngineSystem.h"

class DLL_LOAD IMusic
{
protected:
	//Double buffer
	char * _sound_data[2];
	int _stream_block_size;
	int _sound_data_size;
	ALuint _buffer[2];
	ALuint _source[1];
	int _frequency;
	int _channels;
	double _total_time;

public:
	IMusic(void);
	virtual ~IMusic(void);

	virtual bool Load(const char * filename)=0;
	virtual void Play()=0;
	virtual void Pause()=0;
	virtual void Stop()=0;
};
