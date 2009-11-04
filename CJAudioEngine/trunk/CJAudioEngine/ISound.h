#pragma once

#include "CJAudioEngineSystem.h"

class ISound
{
protected:
	char * _sound_data;
	int _sound_data_size;
	bool _loaded_correctly;
	ALuint _buffer[1];
	ALuint _source[1];
	int _frequency;
	int _channels;
	double _total_time;

public:
	ISound(void);
	virtual ~ISound(void);

	virtual bool Load(const char * filename)=0;
	virtual void Play()=0;
};
